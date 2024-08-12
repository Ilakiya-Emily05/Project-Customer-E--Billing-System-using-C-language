# Project-Customer-E--Billing-System-using-C-language
The Customer E-Billing System is a straightforward C language application designed to manage and maintain billing information for customers. It incorporates four core functions as given in the problem statement input(), writefile(), search(), and output()—to make various aspects of billing management.
Functions of each given:
1.	input():
o	Purpose: Collects billing information from the user.
o	Details Collected: Includes the customer's name, address, phone number, amount paid, due amount, and payment date.
o	Functionality: Prompts the user for details and stores the input in the structure.
2.	writefile():
o	Purpose: Saves billing records to a file.
o	Functioning: Opens customer_data.txt in append mode to ensure new records are added to the end without overwriting existing data.
o	Data Storage: Writes the contents of the Customer structure to the file, formatted for clarity.
3.	search():
o	Purpose: Allows users to search for specific billing records.
o	Search Criteria: Users can search by customer name or phone number.
o	File Reading: Opens customer_data.txt in read mode, scans for matching records, and displays the found details using the output() function.
o	Feedback: Informs the user if no matching records are found.
4.	output():
o	Purpose: Displays billing records.
o	Functionality: Prints details of a Customer structure, showing all fields including name, address, phone number, paid amount, due amount, and payment date.
