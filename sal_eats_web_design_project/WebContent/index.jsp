<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
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
<head>
<meta charset="UTF-8">
<title>SalEats</title>
<link href='https://fonts.googleapis.com/css?family=Lobster' rel='stylesheet'>
<link rel="stylesheet" href="index.css">
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
<div class= "main_image" style="padding-top: 7vh;"><img src="food.jpg" ></div>
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
<div>
<br>
<h6 style="text-align: center">Made by Sajan Gutta</h6>
</div>
<script src="https://maps.google.com/maps/api/js?key=AIzaSyCeUx0QZX-im176JC0eFqAq0qrXtQ9u8jI"></script>
<script>
var x = document.getElementById("demo");
function getLocation() {
  if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(showPosition, showError);
  } else { 
    x.innerHTML = "Geolocation is not supported by this browser.";
  }
}
function validateSearch(){
	var xhttp = new XMLHttpRequest();
	xhttp.open("GET", "ValidateSearchServlet?name=" + document["search"]["restaurant_name"].value + "&longitude=" + document["search"].longitude.value
			+ "&latitude=" + document["search"].latitude.value + "&sort=" + document["search"].sort.value, false);
	xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	xhttp.send();
	console.log(xhttp.responseText);
	if(xhttp.responseText.trim().length > 0){
		document.getElementById("searchformerror").innerHTML = "<p>" + xhttp.responseText + "</p";
		return false;
	}
	return true;
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
</body>
</html>