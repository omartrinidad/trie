from trie import find, insert, create_node
import pickle

path = "zip_codes.pickle"
with open(path, "rb") as zip_codes:
    root = pickle.load(zip_codes)
