# USC Schedule Generator (SChedget)

This directory contains the code for a project I wrote for a Computer Science class at USC. It is a Dynamic Web Project written in Java (using the Eclipse IDE). The purpose of the web application is to provide a place where USC students can enter the classes they will be taking in an upcoming semester, enter time preferences, and be automatically given a schedule that fits their constraints. More information about how all of this works is below.

# Running the application in Eclipse
**STEPS**
1. Install Eclipse
2. Clone this repository to your local computer
3. Create a new dynamic web project in Eclipse
4. Uncheck the box that says use default location
5. Change the location to be this directory (select the directory called "usc_schedule_generator")
6. Choose your desired name for the project and click Finish. You will the see the application created as a project on the left side of Eclipse
7. Follow the steps in the section below to configure the database
8. Update course data to fit your new semester by changing the url inside of Scraper.java to use the course website for the current semester.
9. Run the scraper file once to populate the database with the latest course data (future plans are to restart the central database so all user's have access to current course data)
10. Once all steps above are complete, you can run the project on your local web server and access it through localhost in your browser

## Configuring the Database

1. This project was created using an AWS mySQL database. However, at the time you are seeing this, the database has likely been discontinued to avoid fees.
2. A script has been provided in this directory called "create_201_db.sql" which can be run on your local mySQL server to create the database.
3. Once this is done, make sure to make the proper changes to the credentials inside of the Database.java file. You can find this file inside of the src folder, under the final_project package.
4. Once these steps are complete, the database is properly initialized and you are ready to run the USC schedule generator on your local web server.


# General Functionalities Provided

1. Users can create an account or use the application as a guest.
2. Users can input four courses (or less) that they are taking the next semester. They can also input whether they prefer early, late, or mid-day classes.
3. A schedule is returned based on the above inputs that meets all requirements.
4. Users who are logged in can save the generated schedule
5. Users who are logged in have access to a page with all of their previously saved schedules.

## Future Plans

Future plans include deploying this application to be accessible by a URL, restarting the remote AWS database to allow all users access to current course data, or integrating the algorithms and backend core for this application into USC's own web registration system.

# Languages/Libraries/Concepts Used

- Java (in Eclipse IDE)
- JDBC
- GSON (JSON library in Java)
- Javascript, JQuery, and AJAX
- HTML, CSS, Bootstrap
- JSP, Java Servlets
- Jaunt Web Scraping Library (Java)
- SQL, MySQL Database
- AWS RDS Console
- Recursion/Backtracking when generating the schedule
- Object-Oriented Programming
