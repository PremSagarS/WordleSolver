from enum import Enum

# CONSTANTS for matches
class MatchType(Enum):
    GREY = "0"
    YELLOW = "1"
    GREEN = "2"

def encode(results: list[MatchType]):
    string = ""
    for result in results:
        string += result.value
    return int(string, base = 3)

def decodeFromUserInput(inp: str) -> list[MatchType]:
    retval = []
    for char in inp:
        if char == '0':
            retval.append(MatchType.GREY)
        elif char == '1':
            retval.append(MatchType.YELLOW)
        elif char == '2':
            retval.append(MatchType.GREEN)
    return retval

if __name__ == "__main__":
    print(encode([MatchType.GREEN, MatchType.GREEN, MatchType.GREEN]))