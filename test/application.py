import os
import sys
import pytz

from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash



app = Flask(__name__)

@app.route('/')
def index():
    return render_template("index.html")

@app.route('/process', methods=['POST'])
def process():

	message = request.form.get('message')
	username = request.form.get('username')

	return jsonify({'username' : username, "message" : message})

if __name__ == '__main__':
	app.run(debug=True)