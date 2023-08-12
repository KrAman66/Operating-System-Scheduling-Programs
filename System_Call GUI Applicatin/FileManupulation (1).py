import tkinter as tk
from tkinter import filedialog, messagebox, simpledialog
import shutil
import os

root = tk.Tk()
root.title("File Manager")
root.geometry("800x600")
root.configure(bg="black")  # Set the background color of the root window to black

output_text = tk.Text(root, height=15, width=90, font=("Arial", 12), bg="black", fg="green")
output_text.pack(pady=10)

frame = tk.Frame(root, bg="black")  # Set the background color of the frame to black
frame.pack()

def create_file():
    directory_path = filedialog.askdirectory()
    if directory_path:
        new_file = simpledialog.askstring("Create File", "Enter the name for the new file:")
        if new_file:
            new_file_path = os.path.join(directory_path, new_file)
            with open(new_file_path, "w") as file:
                file.write("")
            output_text.insert(tk.END, f"New file Successfully created: {new_file_path}\n")
            output_text.see(tk.END)

def copy_file():
    file_path = filedialog.askopenfilename()
    if file_path:
        global clipboard_file
        clipboard_file = file_path
        output_text.insert(tk.END, f"File Successfully copied: {clipboard_file}\n")
        output_text.see(tk.END)

def paste_file():
    global clipboard_file
    if clipboard_file:
        destination_path = filedialog.askdirectory()
        if destination_path:
            shutil.copy2(clipboard_file, destination_path)
            output_text.insert(tk.END, f"File Successfully pasted to: {destination_path}\n")
            output_text.see(tk.END)
        else:
            output_text.insert(tk.END, "No destination path specified.\n")
            output_text.see(tk.END)
    else:
        output_text.insert(tk.END, "No file copied. Please copy a file first.\n")
        output_text.see(tk.END)

def rename_file():
    file_path = filedialog.askopenfilename()
    if file_path:
        new_name = simpledialog.askstring("Rename File", "Enter the new name for the file:")
        if new_name:
            new_file_path = os.path.join(os.path.dirname(file_path), new_name)
            os.rename(file_path, new_file_path)
            output_text.insert(tk.END, f"File Successfully renamed to: {new_file_path}\n")
            output_text.see(tk.END)

def delete_file():
    file_path = filedialog.askopenfilename()
    if file_path:
        confirmation = messagebox.askquestion("Confirmation", f"Are you sure you want to delete '{file_path}'?")
        if confirmation == 'yes':
            os.remove(file_path)
            output_text.insert(tk.END, f"File Successfully deleted: {file_path}\n")
            output_text.see(tk.END)

def create_directory():
    directory_path = filedialog.askdirectory()
    if directory_path:
        new_directory = simpledialog.askstring("Create Directory", "Enter the name for the new directory:")
        if new_directory:
            new_directory_path = os.path.join(directory_path, new_directory)
            os.makedirs(new_directory_path)
            output_text.insert(tk.END, f"New directory created Successfully: {new_directory_path}\n")
            output_text.see(tk.END)

def rename_folder():
    folder_path = filedialog.askdirectory()
    if folder_path:
        new_name = simpledialog.askstring("Rename Folder", "Enter the new name for the folder:")
        if new_name:
            new_folder_path = os.path.join(os.path.dirname(folder_path), new_name)
            os.rename(folder_path, new_folder_path)
            output_text.insert(tk.END, f"Folder renamed to: {new_folder_path}\n")
            output_text.see(tk.END)

def delete_folder():
    folder_path = filedialog.askdirectory()
    if folder_path:
        confirmation = messagebox.askquestion("Confirmation", f"Are you sure you want to delete '{folder_path}'?")
        if confirmation == 'yes':
            shutil.rmtree(folder_path)
            output_text.insert(tk.END, f"Folder deleted: {folder_path}\n")
            output_text.see(tk.END)

def copy_folder():
    folder_path = filedialog.askdirectory()
    if folder_path:
        global clipboard_folder
        clipboard_folder = folder_path
        output_text.insert(tk.END, f"Folder Successfully copied: {clipboard_folder}\n")
        output_text.see(tk.END)

def paste_folder():
    global clipboard_folder
    if clipboard_folder:
        destination_path = filedialog.askdirectory()
        if destination_path:
            shutil.copytree(clipboard_folder, destination_path)
            output_text.insert(tk.END, f"Folder Successfully pasted to: {destination_path}\n")
            output_text.see(tk.END)
        else:
            output_text.insert(tk.END, "No destination path specified.\n")
            output_text.see(tk.END)
    else:
        output_text.insert(tk.END, "No folder copied. Please copy a folder first.\n")
        output_text.see(tk.END)

button_font = ("ROG", 12)
button_color = "green"

create_file_button = tk.Button(frame, text='Create File', command=create_file, font=button_font, padx=10, pady=5, bg=button_color, fg="white")
create_file_button.pack(side="left", padx=5, pady=5)

copy_button = tk.Button(frame, text='Copy File', command=copy_file, font=button_font, padx=10, pady=5, bg=button_color, fg="white")
copy_button.pack(side="left", padx=5, pady=5)

paste_button = tk.Button(frame, text='Paste File', command=paste_file, font=button_font, padx=10, pady=5, bg=button_color, fg="white")
paste_button.pack(side="left", padx=5, pady=5)

rename_button = tk.Button(frame, text='Rename File', command=rename_file, font=button_font, padx=10, pady=5, bg=button_color, fg="white")
rename_button.pack(side="left", padx=5, pady=5)

delete_button = tk.Button(frame, text='Delete File', command=delete_file, font=button_font, padx=10, pady=5, bg=button_color, fg="white")
delete_button.pack(side="left", padx=5, pady=5)

second_line_frame = tk.Frame(root, bg="black")
second_line_frame.pack()

create_directory_button = tk.Button(second_line_frame, text='Create Folder', command=create_directory, font=button_font, padx=10, pady=5, bg=button_color, fg="white")
create_directory_button.pack(side="left", padx=5, pady=5)

rename_folder_button = tk.Button(second_line_frame, text='Rename Folder', command=rename_folder, font=button_font, padx=10, pady=5, bg=button_color, fg="white")
rename_folder_button.pack(side="left", padx=5, pady=5)

delete_folder_button = tk.Button(second_line_frame, text='Delete Folder', command=delete_folder, font=button_font, padx=10, pady=5, bg=button_color, fg="white")
delete_folder_button.pack(side="left", padx=5, pady=5)

#copy_folder_button = tk.Button(second_line_frame, text='Copy Folder', command=copy_folder, font=button_font, padx=10, pady=5, bg=button_color, fg="white")
#copy_folder_button.pack(side="left", padx=5, pady=5)

#paste_folder_button = tk.Button(second_line_frame, text='Paste Folder', command=paste_folder, font=button_font, padx=10, pady=5, bg=button_color, fg="white")
#paste_folder_button.pack(side="left", padx=5, pady=5)

root.mainloop()
