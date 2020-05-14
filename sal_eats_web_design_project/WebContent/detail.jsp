<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Details</title>
<link href='https://fonts.googleapis.com/css?family=Lobster' rel='stylesheet'>
<link rel="stylesheet" href="detail.css">
<script src="https://kit.fontawesome.com/bbf7324bbf.js" crossorigin="anonymous"></script>
<%@ page import="gutta_CSCI201L_Assignment4.Restaurant" %>
<style>
	div.backdrop{
	  position: fixed;
	  display: none;
	  background-color: rgba(0,0,0,0.65);
	  top: 0;
	  left: 0;
	  height: 100%;
	  width: 100%; z-index: 100;
	}
	
	div.absolute{
	  position: absolute;
	  margin-left: auto; margin-bottom: auto;
	  margin-right: auto; margin-top: auto;
	  left: 0; top: 0;
	  right: 0; bottom: 0;
	  width: 60vw;
	  height: 60vh;
	  z-index: 110;
	}
</style>
</head>
<body>
<div class="backdrop" id="backdrop">
<div class="absolute" id="mapholder"></div>
</div>
<div class="topnav">
	<ul>
		<li><a href="index.jsp" id="logo">SalEats!</a></li>
		<%Integer id = (Integer) session.getAttribute("user_id");
			if(id == null){%>
				<li><a href="login.jsp" style="padding-top: 50px">Login / Signup</a></li>
				<li><a href="index.jsp" style="padding-top: 50px">Home</a></li>
		<%}else{ %>
				<li><a href="logout" style="padding-top: 50px">Logout</a></li>
				<li><a href="favorites" style="padding-top: 50px">Favorites</a></li>
				<li><a href="index.jsp" style="padding-top: 50px">Home</a></li>
		<%} %>
	</ul>
</div>
<div class="search">
	<form name="search" action="YelpServlet" onsubmit="return validateSearch()">
		<table style="padding-bottom: 2vh">
			<tr style="padding-bottom: 3vh">
				<td style="width: 32%">
					<input name="restaurant_name" id="restaurant_input" placeholder="Restaurant Name" style="text-indent: 1.5%;">
				</td>
				<td style="width: 7%; padding-left: 4%; padding-right: 1.5%;">
					<button id="search_button" type="submit">
						<img src="search.png" style="height: 3vh;">
					</button>
				</td>
				<td style="width: 10%;text-align: center;">
					<input type="radio"  name="sort" value="best_match">
					<label for="Best Match" style="color: grey">Best Match</label><br>
					<input type="radio" name="sort" value="rating">
					<label for="Rating" style="color: grey">Rating</label><br>
				</td>
				<td style="width: 10%;text-align: center">
					<input type="radio" name="sort" value="review_count">
					<label for="Best Match" style="color: grey">Review Count</label><br>
					<input type="radio" name="sort" value="distance">
					<label for="Distance" style="color: grey">Distance</label><br>
				</td>
			<tr>
		</table>
		<table>
			<tr>
				<td style="width: 20%;">
					<input name="latitude" id="location_input" placeholder="Latitude" type="number" step="any" style="text-indent: 1.5%;">
				</td>
				<td style="width: 22%;padding-left: 3%;padding-right: 3%">
					<input name="longitude" id="location_input" placeholder="Longitude" type="number" step="any" style="text-indent: 1.5%;">
				</td>
				<td style="width: 20%">
					<button id="map_button" onclick="getLocation()" type="button">
					<img src="pin.png" style="height: 2vh;"> Google Maps (Drop a Pin!)</button>
				</td>
			<tr>
		</table>
		<p style="color:red;" id="searchformerror"></p>
	</form>
</div>
<% Restaurant restaurant = (Restaurant) request.getAttribute("restaurant");
	String name = restaurant.name;
	String address = restaurant.address;
	String page_link = restaurant.page_link;
	String image_link = restaurant.image_link;
	int rating = restaurant.rating;
	String yelp_id = restaurant.yelp_id;
	String phone_number = restaurant.phone_number;
	String cuisine = restaurant.cuisine;
	String price = restaurant.price;%>
<div style="padding-left: 5vw; padding-right: 5vh">	
	<h1 style="color: grey; font-weight: normal;" id="restaurant_name"><%= name %></h1>
</div>
<div style="color: grey; padding-left: 5vw; padding-right: 5vw;">
	<div style="border-bottom: 1px dashed grey; border-top: 1px dashed grey; height: 55vh" id="stupid_border">
	<table>
		<tr style="display:block; height: 35vh; object-fit: fill">
			<td style="object-fit: fill; width: 40vh; padding-left: 4vw;" valign="middle">
				<div style="display: block; height: 34vh; width: 34vh; padding-top: 3vh; padding-bottom: 3vh;">
					<a href="<%= page_link %>">
					<img src="<%= image_link %>" style="object-fit: fill;border-radius: 30px;" width="100%" height="100%">
					</a>
				</div>
			</td>
			<td style="object-fit: fill; width: 90vh; padding-left: 7%; height: 100%; float: top;" valign="top">
				<div style="display: block; height: 100%; float: top; padding-top: 2vh;">
					<h3 style="font-weight: normal;" id="address">Address: <%= address%></h3>
					<h3 style="font-weight: normal;">Phone No: <%= phone_number%></h3>
					<h3 style="font-weight: normal;">Cuisine: <%= cuisine %></h3>
					<h3 style="font-weight: normal;">Price: <%= price %></h3>
					<h3 style="font-weight: normal;">Rating: <%for(int i=0; i<rating; i++){%> <i class="fas fa-star"></i> <%} %></h3></a><br>
				</div>
			</td>
		</tr>
	</table>
	<button id="favorite" style="width: 100%; background-color: #FFCC00; height: 6vh; margin-bottom: 1vh; 
	border-radius: 5px; border: none; font-size: 2vh; color: grey;" onclick="favorite('<%=restaurant.yelp_id%>')">
		<p><i class="fas fa-star"></i> 
		<%boolean is_favorite = (boolean) request.getAttribute("favorite");
		if(!is_favorite){%>Add to Favorites<%}else{ %> Remove from Favorites<% } %></p></button>
	<button style="width: 100%; background-color: #990000; color: white; height: 
	6vh; border-radius: 5px; border: none; font-size: 2vh;"  onclick="showReservation()">
		<i class="far fa-calendar-plus"></i> Add Reservation</button>
	</div>
</div>
<div style="display: none;" id="add_reservation">
	<form class="reserve" onsubmit="return false" id="reserve">
		<table>
			<tr>
				<td style="width: 45vw; padding-right: 1vw; padding-bottom: 1.7vh;">
					<input onfocus="(this.type='date')" id="date_input" placeholder="Date" style="text-indent: 3%;" name="date">
				</td>
				<td style="width: 45vw; padding-left: 1vw;  padding-bottom: 1.5vh;">
					<input onfocus="(this.type='time')" id="time_input" placeholder="Time" style="text-indent: 3%;" name="time">
				</td>
			</tr>
			<tr>
				<td colspan="2" style="padding-bottom: 1.7vh;">
				<textarea name="notes" id="reservation_input_area" placeholder="Reservation Notes" style="text-indent: 1.5%;"></textarea>
				</td>
			</tr>
		</table>
		<button id="submit-reservation" style="width: 100%; margin-left: 0.1vw; background-color: #990000; color: white; height: 6vh; border-radius: 5px; border: none; font-size: 2vh;">
		<i class="far fa-calendar-plus"></i> Submit Reservation</button>
	</form>
	<p style="color:red; padding-left: 5vw;" id="reservation_error"></p>
</div>
<p style="color:red; padding-left: 5vw;" id="google_error"></p>
<br>
<h6 style="text-align: center">Made by Sajan Gutta</h6>
</div>
<script src="https://maps.google.com/maps/api/js?key=AIzaSyCeUx0QZX-im176JC0eFqAq0qrXtQ9u8jI"></script>
<script>
function validateSearch(){
	var xhttp = new XMLHttpRequest();
	xhttp.open("GET", "ValidateSearchServlet?name=" + document["search"]["restaurant_name"].value + "&longitude=" + document["search"].longitude.value
			+ "&latitude=" + document["search"].latitude.value + "&sort=" + document["search"].sort.value, false);
	xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	xhttp.send();
	console.log(xhttp.responseText);
	if(xhttp.responseText.trim().length > 0){
		document.getElementById("searchformerror").innerHTML = "<p>" + xhttp.responseText + "</p>";
		return false;
	}
	return true;
}
function showReservation(){
	var goog = "<%= session.getAttribute("google")%>"
	if(!goog.localeCompare("yes")){
		if(document.getElementById("add_reservation").style.display == "none"){
			document.getElementById("stupid_border").style["border-bottom"] = "none";
			document.getElementById("add_reservation").style.display = "block";
		}else if(document.getElementById("add_reservation").style.display == "block"){
			document.getElementById("stupid_border").style["border-bottom"] = "1px dashed grey";
			document.getElementById("add_reservation").style.display = "none";
		}
	}else{
		console.log("about to fail");
		document.getElementById("google_error").innerHTML = "<p> Must be logged into Google </p>";
	}
}
function favorite(id){
	console.log(id);
	if(<%=session.getAttribute("user_id")%> == null){
		return true;
	}
	var xhttp = new XMLHttpRequest();
	xhttp.open("GET", "AddFavoritesServlet?yelp_id=" + id, false);
	xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	xhttp.send();
	if(xhttp.responseText.trim() == "yes"){
		document.getElementById("favorite").innerHTML = "<i class='fas fa-star'></i> Remove from Favorites";
		return true;
	}if(xhttp.responseText.trim() == "no"){
		document.getElementById("favorite").innerHTML = "<i class='fas fa-star'></i> Add to Favorites";
		return true;
	}
	return true;
} 
var x = document.getElementById("demo");
function getLocation() {
  if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(showPosition, showError);
  } else { 
    x.innerHTML = "Geolocation is not supported by this browser.";
  }
}

function showPosition(position) {
  var lat = position.coords.latitude;
  var lon = position.coords.longitude;
  var latlon = new google.maps.LatLng(lat, lon)
  var mapholder = document.getElementById('mapholder')

  var myOptions = {
    center:latlon,zoom:14,
    mapTypeId:google.maps.MapTypeId.ROADMAP,
    mapTypeControl:false,
    navigationControlOptions:{style:google.maps.NavigationControlStyle.SMALL}
  }
    
  var map = new google.maps.Map(document.getElementById("mapholder"), myOptions);
  document.getElementById("backdrop").style.display = "block";
  google.maps.event.addListener(map,'click',function(event) {               
	      document.getElementsByName('latitude')[0].value = event.latLng.lat();
	      document.getElementsByName('longitude')[0].value =  event.latLng.lng();
	      document.getElementById("mapholder").innerHTML = "";
	  	  document.getElementById("backdrop").style.display = "none";
	});
}

function showError(error) {
  switch(error.code) {
    case error.PERMISSION_DENIED:
      x.innerHTML = "User denied the request for Geolocation."
      break;
    case error.POSITION_UNAVAILABLE:
      x.innerHTML = "Location information is unavailable."
      break;
    case error.TIMEOUT:
      x.innerHTML = "The request to get user location timed out."
      break;
    case error.UNKNOWN_ERROR:
      x.innerHTML = "An unknown error occurred."
      break;
  }
}
</script>
<script>
  var GoogleAuth;
  var SCOPE = 'https://www.googleapis.com/auth/calendar';
  function handleClientLoad() {
    // Load the API's client and auth2 modules.
    // Call the initClient function after the modules load.
    gapi.load('client:auth2', initClient);
  }

  function initClient() {
    // Retrieve the discovery document for version 3 of Google Drive API.
    // In practice, your app can retrieve one or more discovery documents.
    var discoveryUrl = 'https://www.googleapis.com/discovery/v1/apis/calendar/v3/rest';

    // Initialize the gapi.client object, which app uses to make API requests.
    // Get API key and client ID from API Console.
    // 'scope' field specifies space-delimited list of access scopes.
    gapi.client.init({
        'apiKey': 'AIzaSyCeUx0QZX-im176JC0eFqAq0qrXtQ9u8jI',
		'clientId': '187007187865-kvpt9eraejgfmv22m41jj1c1794tgj81.apps.googleusercontent.com',
        discoveryDocs: [discoveryUrl],
        scope: SCOPE
    }).then(function () {
      // Call handleAuthClick function when user clicks on
      //      "Sign In/Authorize" button.
      GoogleAuth = gapi.auth2.getAuthInstance();
      GoogleAuth.signOut();
      gapi.auth2.getAuthInstance().isSignedIn.listen(addRes);
      
      $('#submit-reservation').click(function() {
		if(document.getElementById('date_input').value == "" || document.getElementById('time_input').value == "" || document.getElementById('reservation_input_area').value == ""){
			document.getElementById('reservation_error').innerHTML = "<p> Must fill in all fields properly </p>";
		}else{
			document.getElementById('reservation_error').innerHTML = "";
			GoogleAuth.signIn();
		}
      });
    });
  }

	Date.prototype.addHours = function(h) {
	  this.setTime(this.getTime() + (h*60*60*1000));
	  return this;
	}

  function addRes(){
	if(gapi.auth2.getAuthInstance().isSignedIn.get()){
		var location = document.getElementById('address').innerHTML;
		var summary = document.getElementById('restaurant_name').innerHTML;
		var start_time = document.getElementById('date_input').value + "T" + document.getElementById('time_input').value;
		var start_date = new Date(start_time);
		var end_date = new Date(start_time);
		end_date.addHours(1);
		console.log(start_date.toString());
		console.log(start_date.toISOString());
		console.log(end_date.toISOString());
		var notes = document.getElementById('reservation_input_area').value;
		var resource = {
		     "summary": summary,
		     "location": location,
			 "description": notes,
		     "start": {
		       "dateTime": start_date.toISOString()
		     },
		     "end": {
		       "dateTime": end_date.toISOString()
				
		     }
		   };
		   var request = gapi.client.calendar.events.insert({
		     'calendarId': 'primary',
		     'resource': resource
		   });
		   request.execute(function(resp) {
		     console.log(resp);
		   });
		   gapi.auth2.getAuthInstance().signOut();	
		}
	}
</script>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
<script async defer src="https://apis.google.com/js/api.js"
        onload="this.onload=function(){};handleClientLoad()"
        onreadystatechange="if (this.readyState === 'complete') this.onload()">
</script>
</body>
</html>

