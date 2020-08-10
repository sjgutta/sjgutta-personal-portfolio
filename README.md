# Sajan Gutta's Personal Portfolio
Contents of this README include my general and contact information (including resume and LinkedIN), programming languages, libraries, and APIs I'm experienced in, descriptions of my work at Discotech and Northrop Grumman (since I can't include any code from those jobs here for confidentiality reasons), and a list of things that I have not included in this repository.
## Coming Soon
- I have recently completed an event recommendation system for Discotech. This was a major undertaking and utilizes a hybrid model of both Collaborative Filtering and Content-Based Filtering to derive recommendations. I gained great Machine Learning experience and utilized Tensorflow for a large portion of the project.
- The release has been delayed due to club closures decreasing the number of events on the Discotech app. When event numbers and traffic restore, it will be deployed and I plan to write a blog/article about the implementation of our event recommendation system. The code will be provided in that and included here at that time.
- The event recommendation system is particularly unique because most recommendation systems have a relatively static inventory (e.g. movies at Netflix). However, at Discotech we have a constantly changing inventory of events we want to consider for recommendation that is dependent on time. As a result, the recommendation system is more complex than the usual solutions.
## Contact and General Information
- I am currently a Junior majoring in Computer Science and Business Administration at the University of Southern California. 
- I intend to complete a Master in Computer Science through USC as well. This would be through a Progressive Degree Program so it would only be an extra year. Since I am on track to graduate a semester early, I would have the Masters in Fall 2022. 
- I'm interested in pursuing a career in analytics or machine learning, applying my Computer Science background.
- Cell: 321-507-8515
- To learn more about my past experience, you can view my LinkedIN profile at https://www.linkedin.com/in/sajan-gutta/ or my resume which is in a pdf file above, located in this directory.

## Languages/APIs/Libraries/Skills
This is not an exhaustive list but covers the languages and libraries that I have the most experience and knowledge working with.
- Python
- Java
- C++ and C
- HTML, CSS, Bootstrap, MVC Model, XML
- JSP, Java Servlets
- Javascript, jQuery, AJAX
- LabView
- Web Scraping (Python Scrapy library, Jaunt Java library)
- Flask, flask-admin in Python
- Relational Databases: SQL, MySQL, Peewee ORM, JDBC, MS SQL Server, pyodbc
- WordPress
- UML, pydocs, tkinter, web sockets and server programming, multi-threading in Python and Java, python requests
- Batch files, shell scripts
- Google Maps API, Google Oauth2 and Sign-in API, Google Calendar API
- Yelp Fusion API
- Visual Basic for Applications

## Discotech Role
During the school year at USC, I have been working part-time as a Backend Developer at a startup called Discotech, headquartered in Los Angeles. Discotech is the #1 Nightlife App and used by people around the world to facilitate easy bookings at venues for their night out. I'm the only college kid in a paid and non-intern position. My role has involved working to improve the backend and add new features that will allow Discotech's business to grow. Through this role, I have gained great professional experience in Backend Design (I've also done some Web Development). The startup environment has allowed me to gain a very hands-on role as a college student and to be regularly assigned significant projects that have developed my programming abilities.
### Notable projects/tasks completed
* Implemented an event recommendation system based on a hybrid of content-based filtering and collaborative filtering. Used Tensorflow for the collaborative filtering part of the project.
  - This was a significant project that took up its own self-contained section of the application. I created classes to generate user preference models, models based on event features, and recommendations based on those models (content-based filtering). I utilized Tensorflow to conduct matrix factorization based on user interactions and generate embeddings to determine recommendations (collaborative filtering).
  - I also built a tool in Discotech's admin site to monitor and maintain the recommendation tool. While most of the project involved backend Python code and modifications to a mySQL database, this part of the system involved some web development in flask-admin.
* Created an event prioritization system/metric to determine the order in which events scraped from venue's website should be reviewed before being pushed live to Discotech's site.
* Designed and implemented an object oriented redirect system for Discotech's web application. Many of the old links for venues, cities, events, etc. have been changed but we don't want existing links to break.
  - Created a view in Flask admin to create redirect cases for specific objects. For example, the city Los Angeles could be redirected from /la to /los-angeles if that slug was changed.
  - This object-oriented design allowed for recursive redirection of paths. Thus, if both the city and venue parts of a path have been changed, both could be changed in the redirect by using the target objects and finding their new slugs.
* Implemented asynchronous task (using Celery) to check for broken tickets links, generate an HTML report, and email it to the ops team. This also required the python requests library.
* Built a Python tool to perform mass updates (e.g. removing a specific contact form from 100's of pages at once without manually clicking through them all) of the Discotech Wordpress site via the WordPress API.
* Helped migrate an assigned section of the codebase to Python 3 before the Python 2 end of life.
* Performed routine bug-fixing and maintenance to repair web scrapers that stopped working.
* Refactored the event scraping process and created asynchronous tasks (in Celery) to minimize slowdowns it could cause on the main application.
* Implemented asynchronous methods to compare event images when doing event scraping.
  - The system flags any changes in event information so that they can be reviewed and udpated on the main site. However, venues would often make slight changes to their images or even just the URLs, leading to excessive event changes that needed to be reviewed but were meaningless.
  - I implemented an asynchronous image comparison system to help identify these unecessary cases and prevent them from being flagged as changes the needed review.
* In addition to the tasks above, I consistenly help out with other smaller tasks such as refactoring sections of code, identifying and fixing bugs, or making improvements to existing features.

## Northrop Grumman Role
I spent the summer of 2019 as a Systems Engineering Intern at Northrop Grumman on a Cybersecurity team developing tools to be used company-wide for improved security analysis and risk mitigation. I was a Software Engineering Intern at Northrop Grumman for summer 2020. In 2020 I was the team lead for 11 interns and we placed Best Overall out of 35 teams in the annual Explore Aerospace Event for 2020, with over 1000 attendees in the company, for our work on secure satellite communications for the military. I was also selected by managers for the Bravo to our Stars Employee Recognition and received a bonus as an intern! In 2019, I was given the Top Performer designation for my performance throughout the summer.
### PLEM Test Scripts (Summer 2020)
* I worked on the Advanced EHF program, producing satellites to provide secure military communications throughout the world for the United States.
* I developed a full suite of python scripts and utilities for conducting crosslink configurations of the satellites and collecting radiometric data. This was a great experience and being able to run my code on an actual satellite in space during significant payload activation was fulfilling. My code was used during the final and most integral step of activation.
* In total, the project was about 4,000 LOC. It was written mostly in Python but also included some XML. I gained great experience writing a server program, working with the socket library to communicate with a payload, creating batch files and shell scripts to launch my code, and designing Python GUI's for user-friendly operation of the code on the satellites.
* For obvious reasons, the contents of my work were classified so I am unable to share them here. However, the work was high quality and had to meet industry standards before being run in an active environment. This code was much more high level than the typical tasks completed in school and greatly improved my development skills.
### Constraint File Generator (Summer 2020)
* When a payload runs commands, it must first check a set of constraints depending on the command, to ensure that the hardware and environment are properly configured to execute that command successfully.
* I wrote an object-oriented Python parsing and conversion system to convert SQL database information about commands, constraints, and their associated formulas and logical relationships into postfix notation files that can be run on the payload. This system can parse and generate all constraints files in under one second due to the object-oriented approach.
* The program and nature of the commands and constraints is classified.
### LabView Work (Summer 2020)
* I can't share much about the specifics of the work, but I worked on some classified LabView programs operating on hardware for the Advanced EHF program. 
* I also created a full application build of my LabView work with an executable for future use.
* Working in a graphically-based language like LabView was a unique experience as most of my programming has been text-based.
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
* This repository is always in progress. I have a number of projects I am currently working on separately (including a web application that allows users to manage their fantasy sports lineups, see live results, and see live scores of their favorite teams all in one place) which will be added here with complete README descriptors when they are complete.
