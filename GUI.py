import tkinter as tk
from tkinter import messagebox

# Create the main application window
root = tk.Tk()
root.title("Academic Management System")
root.geometry("600x400")

# Function to show the dashboard based on the role
def show_dashboard(role):
    # Clear the window
    for widget in root.winfo_children():
        widget.destroy()

    # Display role-specific dashboard
    if role == "Student":
        tk.Label(root, text="Student Dashboard", font=("Helvetica", 16)).pack(pady=20)
        tk.Button(root, text="View Schedule", width=20).pack(pady=5)
        tk.Button(root, text="Add/Drop Courses", width=20).pack(pady=5)
        tk.Button(root, text="Personal Info", width=20).pack(pady=5)
    elif role == "Instructor":
        tk.Label(root, text="Instructor Dashboard", font=("Helvetica", 16)).pack(pady=20)
        tk.Button(root, text="View Class List", width=20).pack(pady=5)
        tk.Button(root, text="Manage Courses", width=20).pack(pady=5)
        tk.Button(root, text="Personal Info", width=20).pack(pady=5)
    elif role == "Admin":
        tk.Label(root, text="Admin Dashboard", font=("Helvetica", 16)).pack(pady=20)
        tk.Button(root, text="Add Course", width=20).pack(pady=5)
        tk.Button(root, text="Remove Course", width=20).pack(pady=5)
        tk.Button(root, text="View All Courses", width=20).pack(pady=5)
        tk.Button(root, text="View Users", width=20).pack(pady=5)
        tk.Button(root, text="Add/Remove Users", width=20).pack(pady=5)
    
    tk.Button(root, text="Logout", command=lambda: login_screen()).pack(pady=20)

# Function to handle login
def login():
    email = email_entry.get()
    role = role_var.get()

    # In a full implementation, this would authenticate against the database
    if email and role:
        show_dashboard(role)
    else:
        messagebox.showerror("Error", "Please enter your email and select a role")

# Function to display the login screen
def login_screen():
    # Clear the window
    for widget in root.winfo_children():
        widget.destroy()

    tk.Label(root, text="Academic Management System", font=("Helvetica", 18)).pack(pady=20)
    tk.Label(root, text="Email:").pack(pady=5)
    global email_entry
    email_entry = tk.Entry(root, width=30)
    email_entry.pack(pady=5)

    tk.Label(root, text="Select Role:").pack(pady=5)
    global role_var
    role_var = tk.StringVar(value="Student")
    tk.Radiobutton(root, text="Student", variable=role_var, value="Student").pack(anchor="w")
    tk.Radiobutton(root, text="Instructor", variable=role_var, value="Instructor").pack(anchor="w")
    tk.Radiobutton(root, text="Admin", variable=role_var, value="Admin").pack(anchor="w")

    tk.Button(root, text="Login", command=login).pack(pady=20)

# Start with the login screen
login_screen()

# Run the application
root.mainloop()
