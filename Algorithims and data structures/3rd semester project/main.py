from tkinter import *
from PIL import Image, ImageTk
from data_structures import Trie, word_to_seq

# Constants
BUTTON_WIDTH = 100
BUTTON_HEIGHT = 100
BACKGROUND_COLOR = '#878787'
MAIN_WINDOW_GEOMETRY = '305x650'
CORPUS = 'MITwordlist.10000.txt'

# Globals - the necessary evil
WORD_SEQ = []
TEXT = ''
NUMBER_MODE = 0  # allows to write numbers, set to 0 every 3 seconds, above 2 clicks means number, above 4 means delete


def reset_number_mode():
    global NUMBER_MODE
    NUMBER_MODE = 0
    root.after(3000, reset_number_mode)


def click(number):
    """"" Add number to current search """
    global NUMBER_MODE
    if NUMBER_MODE >= 2:
        add_text_onscreen(number)
        NUMBER_MODE = 0
        return None
    WORD_SEQ.append(number)
    words_to_display = []
    DICTIONARY.get_words(''.join(WORD_SEQ), words_to_display)
    current_words.delete(0, current_words.size())
    [current_words.insert(END, word) for word in words_to_display]
    current_words.select_set(0)
    current_words.event_generate('<<ListboxSelect>>')
    NUMBER_MODE = 0


def next_word():
    """" Allow to shift user's choice of word (* button) """
    index = current_words.curselection()[0]+1
    if index == current_words.size():
        index = index % current_words.size()

    current_words.select_clear(0, current_words.size())
    current_words.select_set(index)


def add_text_onscreen(to_add):
    """ Display text on screen and clears user's choices so far"""
    global WORD_SEQ, NUMBER_MODE
    if to_add == '':
        NUMBER_MODE += 1
    if NUMBER_MODE >= 4:
        new_text = text.cget('text').rsplit(' ', 1)
        if len(new_text) == 1:
            text.config(text='')
        else:
            text.config(text=new_text[0])
        NUMBER_MODE = 0
        return None
    new_text = text.cget('text')
    new_text += to_add
    text.config(text=new_text)
    WORD_SEQ = []
    current_words.delete(0, current_words.size())


def get_current_word():
    """ Basically needed only for func add_text_onscreen """
    try:
        return current_words.get(current_words.curselection()[0])
    except IndexError:
        return ''


# Main window setup
root = Tk()
root.title('T9 Dictionary GUI')
root.geometry(MAIN_WINDOW_GEOMETRY)
root.resizable(False, False)
root.configure(background=BACKGROUND_COLOR)

# Loading graphics
image_0 = ImageTk.PhotoImage(Image.open('graphics/0.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_1 = ImageTk.PhotoImage(Image.open('graphics/1.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_2 = ImageTk.PhotoImage(Image.open('graphics/2.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_3 = ImageTk.PhotoImage(Image.open('graphics/3.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_4 = ImageTk.PhotoImage(Image.open('graphics/4.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_5 = ImageTk.PhotoImage(Image.open('graphics/5.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_6 = ImageTk.PhotoImage(Image.open('graphics/6.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_7 = ImageTk.PhotoImage(Image.open('graphics/7.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_8 = ImageTk.PhotoImage(Image.open('graphics/8.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_9 = ImageTk.PhotoImage(Image.open('graphics/9.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_star = ImageTk.PhotoImage(Image.open('graphics/star.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))
image_hash = ImageTk.PhotoImage(Image.open('graphics/hash.png').resize((BUTTON_WIDTH, BUTTON_HEIGHT)))

# Widgets on display
frm = Frame(root, bg=BACKGROUND_COLOR)
frm.pack_propagate(False)
frm.grid()

text = Label(frm, bg='#58804D', fg='black', wraplength=150, bd=0, font=('Perpetua', 20))
text.grid(column=0, row=0, columnspan=2, rowspan=2, sticky='nsew')

current_words = Listbox(frm, height=15, bd=0, bg='#58804D', highlightcolor='grey', highlightthickness=0, selectmode=SINGLE)
current_words.grid(column=2, row=0, columnspan=2)

Button(frm, image=image_1,    bd=0,                                                        width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=0, row=3)
Button(frm, image=image_2,    bd=0, command=lambda: click('2'),                            width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=1, row=3)
Button(frm, image=image_3,    bd=0, command=lambda: click('3'),                            width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=2, row=3, sticky='w')
Button(frm, image=image_4,    bd=0, command=lambda: click('4'),                            width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=0, row=4)
Button(frm, image=image_5,    bd=0, command=lambda: click('5'),                            width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=1, row=4)
Button(frm, image=image_6,    bd=0, command=lambda: click('6'),                            width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=2, row=4, sticky='w')
Button(frm, image=image_7,    bd=0, command=lambda: click('7'),                            width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=0, row=5)
Button(frm, image=image_8,    bd=0, command=lambda: click('8'),                            width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=1, row=5)
Button(frm, image=image_9,    bd=0, command=lambda: click('9'),                            width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=2, row=5, sticky='w')
Button(frm, image=image_star, bd=0, command=next_word,                                     width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=0, row=6)
Button(frm, image=image_0,    bd=0, command=lambda: add_text_onscreen(' '),                width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=1, row=6)
Button(frm, image=image_hash, bd=0, command=lambda: add_text_onscreen(get_current_word()), width=BUTTON_WIDTH, height=BUTTON_HEIGHT, bg=BACKGROUND_COLOR).grid(column=2, row=6, sticky='w')

# Loading dictionary
DICTIONARY = Trie('')
with open(CORPUS) as file:
    while line := file.readline().rstrip().lower():
        if line.isalpha():
            DICTIONARY.insert(word_to_seq(line), line)
        else:
            continue
    print("Done!")

root.after(2000, reset_number_mode)
root.mainloop()
