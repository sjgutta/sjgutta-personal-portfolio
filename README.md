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
- HTML, CSS, Bootstrap
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
