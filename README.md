# Sajan Gutta's Personal Portfolio
Contents of this README include my general and contact information (including resume and LinkedIN), programming languages, libraries, and APIs I'm experienced in, descriptions of my work at Discotech and Northrop Grumman (since I can't include any code from those jobs here for confidentiality reasons), and a list of things that I have not included in this repository.
## Contact and General Information
- I am currently a Sophomore majoring in Computer Science and Business Administration at the University of Southern California. 
- I'm interested in pursuing a career in analytics, applying my Computer Science background. I'm specifically interested in the field of sports analytics.
- Email: gutta@usc.edu or sjgutta@gmail.com
- Cell: 321-507-8515
- To learn more about my past experience, you can view my LinkedIN profile at https://www.linkedin.com/in/sajan-gutta/ or my resume at [LINK COMING SOON].

## Languages/APIs/Libraries
This is not an exhaustive list but covers the languages and libraries that I have the most experience and knowledge working with.
- Python
- Java
- C++ and C
- HTML, CSS, Bootstrap, MVC Model
- JSP, Java Servlets
- Javascript, jQuery, AJAX
- Web Scraping (Python Scrapy library, Jaunt Java library)
- Flask, flask-admin in Python
- Relational Databases: SQL, MySQL, Peewee ORM, JDBC, MS SQL Server, pyodbc
- WordPress
- UML, pydocs
- Google Maps API, Google Oauth2 and Sign-in API, Google Calendar API
- Yelp Fusion API
- Visual Basic for Applications

## Discotech Role
During the school year at USC, I have been working part-time as a Backend Developer at a startup called Discotech, headquartered in Los Angeles. Discotech is the #1 Nightlife App and used by people around the world to facilitate easy bookings at venues for their night out. I'm the only college kid in a paid and non-intern position. My role has involved working to improve the backend and add new features that will allow Discotech's business to grow. Through this role, I have gained great professional experience in Backend Design (I've also done some Web Development). The startup environment has allowed me to gain a very hands-on role as a college student and to be regularly assigned significant projects that have developed my programming abilities.
### Notable projects/tasks completed
* Implemented an event recommendation system based on content-based filtering machine learning
  - This was a significant project that took up its own self-contained section of the application. I created classes to generate user preference models, models based on event features, and recommendations based on those models.
  - I also built a tool in Discotech's admin site to monitor and maintain the recommendation tool. While most of the project involved backend Python code and modifications to a mySQL database, this part of the system involved some web development in flask-admin.
* Created an event prioritization system/metric to determine the order in which events scraped from venue's website should be reviewed before being pushed live to Discotech's site.
* Built a Python tool to perform mass updates (e.g. removing a specific contact form from 100's of pages at once without manually clicking through them all) of the Discotech Wordpress site via the WordPress API.
* Helped migrate an assigned section of the codebase to Python 3 before the Python 2 end of life.
* Performed routine bug-fixing and maintenance to repair web scrapers that stopped working.
* Refactored the event scraping process and created asynchronous tasks (in Celery) to minimize slowdowns it could cause on the main application.
* Implemented asynchronous methods to compare event images when doing event scraping.
  - The system flags any changes in event information so that they can be reviewed and udpated on the main site. However, venues would often make slight changes to their images or even just the URLs, leading to excessive event changes that needed to be reviewed but were meaningless.
  - I implemented an image comparison system to help identify these unecessary cases and prevent them from being flagged as changes the needed review.
* In addition to the tasks above, I consistenly help out with other smaller tasks such as refactoring sections of code or identifying and fixing bugs.

## Northrop Grumman Role
I spent the summer of 2019 as a Systems Engineering Intern at Northrop Grumman on a Cybersecurity team developing tools to be used company-wide for improved security analysis and risk mitigation. I will be a Software Engineering Intern at Northrop Grumman for summer 2020.
### STIG Tracking Tool (Summer 2019)
* Companies that operate on the Department of Defense's classified network must perform and report the results for a large number of cybersecurity assessment protocols created by the DOD. These come in an unclear data format that is difficult to work with. As a result, people at companies such as Northrop must go in and analyze the data by hand, aggregating the useful information. My task was to develop a tool that could take all of this data and normalize it. I ended up taking this much further and providing an array of functionalities to improve cybersecurity assessment at Northrop Grumman.
* Developed my tool to standardize and automate system security STIG assessments and reporting.
* The tracking tool allows storage and analysis of assessment data with the click of a single button on the GUI. 
* The tool also automatically identifies the specific vulnerabilities to be fixed in NG systems (not just the number of vulnerabilities which is what is usually reported), provides instructions to do so, identifies the most common ones throughout the company's systems, and organizes them in order or urgency to create a workflow for cybersecurity engineers to follow when performing risk mitigation. These were all functionalities beyond the initial assignment.
* The project has sector-wide impact and will eventually be adopted by all programs throughout the company.
* The STIG Tracking Tool reduced the reporting process for an engineering team from 60+ hours to less than 5 minutes, allowing for an increased scope of assessments, accurate mitigation (by eliminating human error), and significant cost savings.
* Built using Python, MS SQL Server, and SQL. Mapped full database and class diagram in UML. Created installable company-wide package with scripting to auto-install the necessary Python libraries and automatically create the database on an MS SQL Server. This makes the tool easy for any engineer in the company to install and configure it on their computer, as this only requires clicking a few buttons.
* Built the GUI using the Python Tkinter library. Generated report graphics using python Pillow library. Documented code in Pydocs. Utilized the pyodbc driver to connect to SQL server.
* Complete documentation for this tool was also created using pydocs.
### Northrop Grumman Communications Database (Summer 2019)
* Developed a communications and employee resource management database in MS Access for the NG Cybersecurity Division
* The database has the capability to identify the skills of each employee, determine best fits for open positions, report management and sector changes, and automatically notify employees of these changes. Reports about changes are also automatically generated for management to analyze. This allows for efficient organizational management and distribution of employee capabilities
* Built in MS Access, utilizes SQL for queries, utilized VBA to build database form, macros for automating, and interfaces with the Outlook Object Model.
* Full documentation was also provided to management for this project.

## Missing from this repository
* Discotech work - as mentioned above, I can't provide the code written in any jobs but I have done my best to describe some of the projects I completed and the skills involved
* Northrop Grumman - same as for Discotech
* School work - there is a large amount of school work (100+ labs and assignments) that has also been ommitted from this repository. Most of those pieces of work relate to the skills listed above. I have only included the most significant and unique pieces of work in here.
* This repository is always in progress. I have a number of projects I am currently working on separately (including an application that allows users to click a button on the navbar at the top of their computer and pop-up a window where they can manage their fantasy sports lineups, see live results, and see live scores of their favorite teams) which will be added here with complete README descriptors when they are complete.
