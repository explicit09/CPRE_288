
##-------------------------YouTube video 1: hellow world GUI ------------------------------------ 
#from tkinter import * #This imports everything fom tkinter. in tkinter everything uses a widget

#root = Tk() #this opens a window in tkinter is it the root widget

#--to create anything in kinter you need to 1). define the thing 2). put it up on the screen
#myLabel = Label(root, text = "Hello World!") #1). we are dinfing a variable, so creating a label widget
#myLabel.pack() #shoving the label on to the screen (packaging) --> simplest way to make things fit on screen (forces everything to fit on the window) (text will stay exactly where it appeared (center top)

#root.mainloop() #This is the main loop of the function 


##----------------------------YouTube video 2 : positioning objects -----------------------------------
#same thing as video 1 but this time we are changing 'Pack" to 'grid" so adding rows/columns
#from tkinter import *
#root = Tk()

#myLabel = Label(root, text = "Hello World!")
#myLabe2 = Label(root, text = "This is Netty's first attempt")
#myLabe3 = Label(root, text = " ")

#myLabel.grid(row=0, column=0) #changing this to grid (row=0, column=1)
#myLabe2.grid(row=0, column=5) #same row as the top just changing column #if we said row=0, column=5 it sill still put it next to it because it is a relative measurment
#myLabe3.grid(row=0, column=1) #just spacing out label1 and label 2s

#root.mainloop() 

##---------instead of formatting like above we can change it to like below----
#from tkinter import *
#root = Tk()

#myLabel = Label(root, text = "Hello World!").grid(row=0, column=0)
#myLabe2 = Label(root, text = "This is Netty's first attempt").grid(row=0, column=1)

#root.mainloop() 


##----------------------------YouTube video 3 : Push Button -----------------------------------

#this time we are addding a button widget since everything is widgets in tkiner
# from tkinter import *
# root = Tk()

# myButton = Button(root, text= "Click Me!") #defining button
# myButton.pack()

# #instead of just making a button we can also make a state for the button
# myButton2 = Button(root, text= "Click Me!", state=DISABLED) #defining button
# myButton2.pack()


# #we can also add features like make it bigger
# #instead of just making a button we can also make a state for the button
# myButton3 = Button(root, text= "Click Me!", padx=30, pady=50) #making x or y axis bigger or smaller
# myButton3.pack()


# root.mainloop() 

import tkinter as tk

window = tk.Tk()


def handle_click(event):
    print("The button was clicked!")

button = tk.Button(text="Click me!")

button.bind("<Button-1>", handle_click)

button.pack()

window.mainloop()








