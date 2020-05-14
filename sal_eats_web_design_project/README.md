# SalEats (Completed for a CSCI 201 Web Design Project)

This directory contains the code for a project I wrote for a Computer Science class at USC. It is a dynamic web project created in Eclipse on which users can search for restaurants through the Yelp API, add them to favorites, view their favorites, and create reservations that are added to their google calendar. 
They can also create accounts and even login with their google account. Multiple notable APIs were used in this project and many of the functionalities provided as well as setup instructions are further detailed below.
# Running the application in Eclipse
**STEPS**
1. Install Eclipse
2. Clone this repository to your local computer
3. Create a new dynamic web project in Eclipse
4. Uncheck the box that says use default location
5. Change the location to be this directory (select the directory called "usc_schedule_generator")
6. Choose your desired name for the project and click Finish. You will the see the application created as a project on the left side of Eclipse
7. Configure your local database using the steps provided below.
8. Once all steps above are complete, you can run the project on your local web server and access it through localhost in your browser

## Configuring the Database

1. The script in this directory called create_db.sql can be run to properly create and intialize the database needed for this application to run.
2. The Database.java file in the src folder establishes the application's connection to local database. Make sure to properly change the connection string and credentials there to match your own local database.

# General Functionalities Provided

1. Users can create an account or use the application as a guest.
2. Users can search the Yelp API for restaurants using the following criteria:
      - Users can enter their location based on longitude and latitude. There is a button which pops up a google maps window where users can select their location. This will auto populate the latitude and longitude fields correctly.
      - Users can enter the restaurant name or a keyword to search by
      - Users can sort results by Best Match, Rating, Distance, and Review Count
3. Users can view detail pages of each restaurant. Each result also has information about the restaurant including address, rating, price, cuisine, and a link to its actual Yelp page.
4. Authenticated users can add restaurants to their favorites page and view them on that page. They can also sort the favorites page based on recency, rating, and alphabetically without refreshing the page.
5. Authenticated users can make reservations from the details page of a restaurant on the website. Submitting a reservation will add that reservation as an event on their google calendar.
6. Users have the option to login with their Google account rather than creating an account.

# Notable future improvement

If doing this again in the future, I would have a better structure for my CSS. I would do a better job of condensing the CSS to one main file that can be imported into all the JSP files if possible. I would also make things like the searchbar more modular and something that can be embedded in each page easily rather than copy and pasting code each time.

# Languages/Libraries/APIs Used

- Java (in Eclipse IDE)
- JDBC
- GSON (JSON library in Java)
- Javascript, JQuery, and AJAX
- HTML, CSS
- JSP, Java Servlets
- SQL, MySQL Database
- Yelp Fusion API
- Google OAuth2 and Sign-in API
- Google Maps API
- Google Calendar API
