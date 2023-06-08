import os
import sys

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = :user_id ORDER BY symbol ASC", user_id=session["user_id"])
    print(stocks)
    user = db.execute("SELECT * FROM users WHERE id = :ID", ID=session["user_id"])
    grand_total = 0.0

    for i in range(len(stocks)):
        stock = lookup(stocks[i]["symbol"])
        stocks[i]["company"] = stock["name"]
        stocks[i]["cur_price"] = "%.2f"%(stock["price"])
        stocks[i]["cur_total"] = "%.2f"%(float(stock["price"]) * float(stocks[i]["shares"]))
        stocks[i]["profit"] = "%.2f"%(float(stocks[i]["cur_total"]) - float(stocks[i]["total"]))
        grand_total += float(stocks[i]["cur_total"])
        stocks[i]["total"] = "%.2f"%(stocks[i]["total"])
    #portfolio's value
    grand_total += float(user[0]["cash"])
    #how much all of stocks cost now
    """Show portfolio of stocks"""
    return render_template("index.html", stocks=stocks, cash=usd(user[0]["cash"]), grand_total=usd(grand_total))


@app.route("/register", methods=["GET", "POST"])
def register():
    session.clear()
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        def username():
            username = request.form.get("username")
            return username

        username = request.form.get("username")
        password = request.form.get("password")

        repeat = db.execute("SELECT * FROM users WHERE username = :username", username=username)

        if len(repeat) != 0:
            return apology("this username was already taken")

        confirm_password = request.form.get("confirm_password")

        if password != confirm_password:
            return apology("the passwords are different")

        # Insert username and password into database
        rows = db.execute("INSERT INTO users (username, hash) VALUES (:username, :password) ",
                          username=request.form.get("username"), password=generate_password_hash(password))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide a symbol", 403)

        shares = int(request.form.get("shares"))

        if not shares:
             return apology("must provide a number of shares", 403)

        if shares < 1:
            return apology("must provide a positive number of shares", 403)

        symbol = request.form.get("symbol").upper()
        result = lookup(symbol)

        if result == None:
            return apology("symbol not found", 403)



        user_id = session["user_id"]

        # lookup the stock
        result = lookup(symbol)
        price = result["price"]
        # calculate total price
        total = float(price) * float(shares)

        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)

        funds = float(user[0]["cash"])

        # check if user has enough funds
        if funds < total:
            return apology("not enough funds available: " + str("%.2f"%funds))

        funds_left = funds - total

        # check if symbol is already owned
        stock_db = db.execute("SELECT * FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                            user_id=user_id, symbol=symbol)

        # update with new price if already owned
        if len(stock_db) == 1:

            new_shares =int(stock_db[0]["shares"]) + shares
            new_total = float(stock_db[0]["total"]) + total
            new_price = "%.2f"%(new_total / float(new_shares))

            db.execute("UPDATE stocks SET Shares = :shares, Total = :total, Price = :price WHERE user_id = :user_id AND symbol = :symbol",
                        shares=new_shares, total=new_total, price=new_price, user_id=user_id, symbol=symbol)

        # else create a new entry in db
        else:

            db.execute("INSERT INTO stocks (user_id, Symbol, Shares, Total, Price) VALUES (:user_id, :symbol, :shares, :total, :price)",
                        user_id=user_id, symbol=symbol, shares=shares, total=total, price=result["price"])

        # modify available funds
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=funds_left, id=user_id)

        # commit to history
        db.execute("INSERT INTO history (user_id, Action, Symbol, Shares, Price) VALUES (:user_id, :action, :symbol, :shares, :price)",
                    user_id=user_id, action=1, symbol=symbol, shares=shares, price=result["price"])

        # send a success message
        return render_template("success.html", action="bought", shares=shares,
                                name=result["name"], total=usd(total), funds=usd(funds_left))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM history WHERE user_id = :user_id ORDER BY date DESC", user_id=session["user_id"])

    for i in range(len(stocks)):
        stocks[i]["total"] = "%.2f"%(float(stocks[i]["shares"]) * float(stocks[i]["price"]))

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required

def quote():
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide quote", 403)

        result = lookup(request.form.get("symbol"))

        if result == None:
            return apology("symbol not found", 403)

        # Redirect user to home page
        return render_template("quoted.html", name=result["name"], price=result["price"])

    else:
        return render_template("quote.html")

@app.route("/quoted")
def quoted():
    return render_template("quoted.html")





@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = :user_id", user_id=session["user_id"])

    if request.method == "POST":

        user_id = session["user_id"]
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not symbol:
            return apology("must prvide symbol", 403)

        if not shares:
            return apology("must provide a number of shares", 403)

        stock_db = db.execute("SELECT * FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                            user_id=user_id, symbol=symbol)
        if stock_db:
            stock_db = stock_db[0]
        else:
            return apology("you don't own such a share")

        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)

        if int(shares) < 1:
            return apology("must provide a positive number", 403)

        if int(shares) > stock_db["shares"]:
            return apology("not enough shares available: " + str(stock_db["shares"]))

        stock = lookup(symbol)

        # calculate total price
        total_price = float(stock["price"]) * float(shares)

        # modify number of shares owned or delete if == 0
        if int(shares) == stock_db["shares"]:
            db.execute("DELETE FROM stocks WHERE user_id = :user_id AND symbol = :symbol", user_id=user_id, symbol=symbol)
        else:
            new_shares = int(stock_db["shares"]) - int(shares)
            new_total = float(new_shares) * float(stock_db["price"])
            db.execute("UPDATE stocks SET shares = :shares, total = :total WHERE user_id = :user_id AND symbol = :symbol",
                        shares=new_shares, total=new_total, user_id=user_id, symbol=symbol)

        # modify available funds
        funds_available = float(user[0]["cash"]) + total_price
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=funds_available, id=user_id)

        # commit to history
        db.execute("INSERT INTO history (user_id, action, symbol, shares, price) VALUES (:user_id, :action, :symbol, :shares, :price)",
                    user_id=user_id, action=0, symbol=symbol, shares=shares, price=stock["price"])

        # send a success message
        return render_template("success.html", action="sold", shares=shares,
                                name=stock["name"], total=usd(total_price), funds=usd(funds_available))

    else:
        return render_template("sell.html")
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
