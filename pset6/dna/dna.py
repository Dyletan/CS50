from sys import argv, exit
import csv

def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    with open(argv[1]) as data:
        people = list(csv.reader(data))
        people[0].remove("name")
        STR = people[0]

    with open(argv[2]) as sequence:
        dna = sequence.read()

    valuelist = list(map(str, get_longest_seq(dna, STR)))
    #make a new list to preserve reader
    cleaned = people
    cleaned.pop(0)
    #compare valuelist to reader and if found print the name of the person whos DNA has all the occurances to the console/terminal.
    for person in cleaned:

        if person[1:] == valuelist:
            print(f"{person[0]}")
            break

        elif person == cleaned[-1]:
            print("No match")


def get_longest_seq(s, sub):

    valuelist = []

    for i in range(len(sub)):
        maxcounter = 0
        counter = 0
        position = 0
        previouspos = 0
        # while the dna sequence has not been fully scanned through do the following.
        while position < len(s):
            # this gives the position at which the sequence is found
            position = s.find(sub[i], position)

            if position == -1: # i.e not found, reset the counter, stop the loop.
                counter = 0
                break
            # if not -1 then the sequence being searched for has been found and if (position - the length of the sequence) is also equal to 0, it is a consequtive value
            #if sequence is at the start of the sequence
            elif previouspos == 0:
                counter += 1
                maxcounter = counter
                previouspos = position
            #sequential occurances
            elif position - len(sub[i]) == previouspos:
                counter += 1
                previouspos = position
                if maxcounter < counter:
                    maxcounter = counter
            #first found and not at the start of the sequence.
            elif position - len(sub[i]) != previouspos:
                counter = 1
                previouspos = position
                if maxcounter < counter:
                    maxcounter = counter

            position += 1

        valuelist.append(maxcounter)

    return valuelist

main()
