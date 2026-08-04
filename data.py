from eval import twoWordMatch
from match import MatchType, encode
import pickle

FNAME = "./wordle_answers_2315.txt"

def load_data(txtfilename: str) -> list[str]:
    file = open(txtfilename)
    words = map(stripline, file.readlines())
    return list(words)

def stripline(line: str) -> str:
    return line.strip()

def makeMatrix(words: list[str]) -> list[list[list[MatchType]]]:
    matrix = [[None for i in range(len(words))] for j in range(len(words))]
    for i in range(len(words)):
        for j in range(len(words)):
            matrix[i][j] = twoWordMatch(words[i], words[j])
    pickle.dump(matrix, open("temp-matrix.pkl", "wb"))
    return matrix

def loadMatrix() -> list[list[list[MatchType]]]:
    try:
        return pickle.load(open("temp-matrix.pkl", "rb"))
    except FileNotFoundError:
        return makeMatrix(load_data(FNAME))

def makeDict(matrix: list[list[list[MatchType]]]) -> list[list[int]]:
    retval = [[0 for i in range(243)] for j in range(len(matrix))]
    for guessidx, row in enumerate(matrix):
        for result in row:
            retval[guessidx][encode(result)] += 1
    pickle.dump(retval, open("temp-dict.pkl", "wb"))
    return retval

def loadDict() -> list[list[int]]:
    try:
        return pickle.load(open("temp-dict.pkl", "rb"))
    except FileNotFoundError:
        return makeDict(loadMatrix())


if __name__ == '__main__':
    data = loadDict()
    print((data[0][242]))