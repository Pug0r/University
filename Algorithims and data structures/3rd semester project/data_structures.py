# Dictionary to map letters to number pressed
word_to_seq_dict = dict.fromkeys(['a', 'b', 'c'], '2')
word_to_seq_dict.update(dict.fromkeys(['d', 'e', 'f'], '3'))
word_to_seq_dict.update(dict.fromkeys(['g', 'h', 'i'], '4'))
word_to_seq_dict.update(dict.fromkeys(['j', 'k', 'l'], '5'))
word_to_seq_dict.update(dict.fromkeys(['m', 'n', 'o'], '6'))
word_to_seq_dict.update(dict.fromkeys(['p', 'q', 'r', 's'], '7'))
word_to_seq_dict.update(dict.fromkeys(['t', 'u', 'v'], '8'))
word_to_seq_dict.update(dict.fromkeys(['w', 'x', 'y', 'z'], '9'))


def word_to_seq(word: str) -> str:
    """ Translates word to sequence of numbers """
    result = ''
    for letter in word:
        result += word_to_seq_dict[letter]
    return result


# Basically a list, with insertion and ability to modify order
class PrioritySeq:
    def __init__(self, data: any):
        if data == '':
            self.seq = []
        else:
            self.seq = [data]

    def insert(self, item: any) -> None:
        self.seq.append(item)

    def prior_up(self, item: any) -> int:
        if self.seq[0] == item:
            return 1
        for i, _ in enumerate(self.seq):
            if self.seq[i] == item:
                self.seq[i], self.seq[i - 1] = self.seq[i - 1], self.seq[i]
                return 1
        return -1

    def print(self):
        for elem in self.seq:
            print(elem)

    def get_word_list(self):
        return self.seq


class Trie:
    num_to_name = {'2': 'two',
                   '3': 'three',
                   '4': 'four',
                   '5': 'five',
                   '6': 'six',
                   '7': 'seven',
                   '8': 'eight',
                   '9': 'nine'}

    def __init__(self, data: str):
        self.two = None
        self.three = None
        self.four = None
        self.five = None
        self.six = None
        self.seven = None
        self.eight = None
        self.nine = None
        if data == '':
            self.data = PrioritySeq('')
        else:
            self.data = PrioritySeq(data)

    def insert(self, seq: str, word: str) -> None:
        attr_name = self.num_to_name[seq[0]]
        if len(seq) == 1:
            if getattr(self, attr_name) is None:
                setattr(self, attr_name, Trie(word))
            else:
                getattr(self, attr_name).data.insert(word)
        else:
            if getattr(self, attr_name) is None:
                setattr(self, attr_name, Trie(''))
                getattr(self, attr_name).insert(seq[1:], word)
            else:
                getattr(self, attr_name).insert(seq[1:], word)

    def get_words(self, seq: str, container: list) -> list:
        try:
            if not len(seq) == 1:
                return getattr(self, self.num_to_name[seq[0]]).get_words(seq[1:], container)
            else:
                return self.words_below(getattr(self,  self.num_to_name[seq]), container)
        except AttributeError:
            return []

    def words_below(self, root, container: list) -> list:
        container.extend(root.data.get_word_list())
        if root.two is not None:
            container.extend(root.two.data.get_word_list())
            self.words_below(root.two, container)
        if root.three is not None:
            container.extend(root.three.data.get_word_list())
            self.words_below(root.three, container)
        if root.four is not None:
            container.extend(root.four.data.get_word_list())
            self.words_below(root.four, container)
        if root.five is not None:
            container.extend(root.five.data.get_word_list())
            self.words_below(root.five, container)
        if root.six is not None:
            container.extend(root.six.data.get_word_list())
            self.words_below(root.six, container)
        if root.seven is not None:
            container.extend(root.seven.data.get_word_list())
            self.words_below(root.seven, container)
        if root.eight is not None:
            container.extend(root.eight.data.get_word_list())
            self.words_below(root.eight, container)
        if root.nine is not None:
            container.extend(root.nine.data.get_word_list())
            self.words_below(root.nine, container)
        return container

    def show(self):
        self.data.print()


if __name__ == "__main__":
    DICTIONARY = Trie('')

# Testing
    with open('MITwordlist.10000.txt') as file:
        while line := file.readline().rstrip().lower():
            if line.isalpha():
                DICTIONARY.insert(word_to_seq(line), line)
            else:
                continue

    words = []
    DICTIONARY.words_below(DICTIONARY.two, words)

    print(len(words))
    test = []
    print(len(DICTIONARY.get_words('2', test)))

