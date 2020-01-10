from trie import find, insert, create_node
import csv
import pickle

root = create_node()

with open("zips.csv", "r", encoding="utf-8-sig") as lco:
    for line in csv.DictReader(lco, delimiter=","):
        insert(root, line["zip"])

path = "zip_codes.pickle"
with open(path, "wb") as zip_codes:
    pickle.dump(root, zip_codes)
