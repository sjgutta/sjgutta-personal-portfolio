import os
from tkinter import *
from tkinter import ttk
from tkinter import filedialog
from trainer import classify_image

LABELS = ["CAT", "DOG"]


class Window(Tk):
    def __init__(self):
        super(Window, self).__init__()
        self.title("Cat/Dog Image Classifier by Sajan Gutta")
        lbl = Label(self, text="Click below to select an image to classify:", font=("Arial Bold", 20), fg="red")
        lbl.grid(column=0, row=0, padx=10)

        ttk.Separator(self, orient=HORIZONTAL).grid(row=1, columnspan=5, sticky="ew")

        self.labelFrame = ttk.LabelFrame(self, text="Open File")
        self.labelFrame.grid(column=0, row=2, padx=20, pady=20)

        classify_button = ttk.Button(self, text="Classify Image", command=self.classify)
        classify_button.grid(column=0, row=5)

        result_label = Label(self, text="Your image is a:", font=("Arial Bold", 15))
        result_label.grid(column=0, row=10)

        self.classified_label = Label(self, text="Result here", font=("Arial", 15))
        self.classified_label.grid(column=0, row=11)

        self.error_label = Label(self, text="", font=("Arial Bold", 15), fg="red")
        self.error_label.grid(column=0, row=20)

        self.create_button()

    def create_button(self):
        self.button = ttk.Button(self.labelFrame, text="Browse A File", command=self.file_dialog)
        self.button.grid(column=1, row=1)

    def classify(self):
        try:
            filename = self.filename
            print(filename)
            result = classify_image("first_try.h5", filename)
            self.classified_label.configure(text=f"{LABELS[result]}!")
            self.error_label.configure(text="")
        except AttributeError:
            self.error_label.configure(text="Must select a filename")

    def file_dialog(self):
        self.filename = filedialog.askopenfilename(initialdir=os.getcwd(), title="Select A File",
                                                   filetypes=(("jpeg files", "*.jpg"), ("all files", "*.*")))
        self.label = ttk.Label(self.labelFrame, text="")
        self.label.grid(column=1, row=2)
        self.label.configure(text=self.filename)
        self.error_label.configure(text="")


window = Window()
window.mainloop()
