<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Your Favorites</title>
<link href='https://fonts.googleapis.com/css?family=Lobster' rel='stylesheet'>
<%@ page import="java.util.ArrayList, gutta_CSCI201L_Assignment4.Restaurant" %>
<script src="https://kit.fontawesome.com/bbf7324bbf.js" crossorigin="anonymous"></script>
<link rel="stylesheet" href="favorites.css">
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
<script src="https://code.jquery.com/jquery-1.10.2.js"
	type="text/javascript"></script>
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
					<label for="Best Match" style="color: grey;">Best Match</label><br>
					<input type="radio" name="sort" value="rating">
					<label for="Rating" style="color: grey;">Rating</label><br>
				</td>
				<td style="width: 10%;text-align: center">
					<input type="radio" name="sort" value="review_count">
					<label for="Best Match" style="color: grey;">Review Count</label><br>
					<input type="radio" name="sort" value="distance">
					<label for="Distance" style="color: grey;">Distance</label><br>
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
<div style="padding-left: 5vw; padding-right: 5vw;">
<h1 style="margin-top: 4vh; margin-bottom: 4vh; color: grey; font-weight: normal;"><%=request.getAttribute("username") %>'s Favorites:
<div class="dropdown">
  <button onclick="openDropdown()" class="dropbtn"><i class="fas fa-sort-amount-down"></i> Sort by <i class="fas fa-caret-down"></i></button>
  <div id="myDropdown" class="dropdown-content">
    <a id="alphabet_sorter_asc">A to Z</a>
    <a id="alphabet_sorter_desc">Z to A</a>
    <a id="rating_desc">Highest Rating</a>
    <a id="rating_asc">Lowest Rating</a>
    <a id="recent_asc">Most Recent</a>
    <a id="recent_desc">Least Recent</a>
  </div></h1>
</div>
</div>
<div class="wrapper" style="padding-right:5vw; padding-left: 5vw;">
<% ArrayList<Restaurant> favorites = (ArrayList<Restaurant>)request.getAttribute("favorites");
	ArrayList<Integer> favorite_ids = (ArrayList<Integer>) request.getAttribute("ids");
	for(int i=0; i<favorites.size(); i++){
		String name = favorites.get(i).name;
		String address = favorites.get(i).address;
		String page_link = favorites.get(i).page_link;
		String image_link = favorites.get(i).image_link;
		int rating = favorites.get(i).rating;
		String yelp_id = favorites.get(i).yelp_id;
		int favorite_id = favorite_ids.get(i);
	%><div style="color: grey; height: 44vh; border-bottom: 1px dashed grey; border-top: 1px dashed grey;" class="item" 
	data-name="<%=name%>" data-rating="<%=rating%>" data-id="<%= favorite_id%>">
	<table style="border-collapse: collapse;">
		<tr style="display: block; height: 100%; padding-top: 2vh; padding-bottom: 2vh; object-fit: fill;">
			<td style="object-fit: fill; width: 38vh; padding-left: 4vw;" valign="middle">
				<div style="display: block; height: 34vh; width: 34vh; padding-top: 3vh; padding-bottom: 3vh;">
					<a href="detail?yelp_id=<%= yelp_id %>">
					<img src="<%= image_link %>" style="object-fit: fill;border-radius: 30px;" width="100%" height="100%">
					</a>
				</div>
			</td>
			<td style="object-fit: fill; width: 90vh; padding-left: 7%; height: 100%; float: top;" valign="top">
				<div style="display: block; height: 100%; float: top; padding-top: 2vh;">
					<h2 id="name"><%= name%></h2>
					<h3 style="font-weight: normal;"><%= address%></h3>
					<a href="<%= page_link %>" style="text-decoration: none; color: grey;"><h3 style="font-weight: normal;"><%= page_link%></h3></a><br>
				</div>
			</td>
		</tr>
		</table>
	</div>
	<%}%>
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
		document.getElementById("searchformerror").innerHTML = "<p>" + xhttp.responseText + "</p";
		console.log("returning false");
		return false;
	}
	console.log("returning true");
	return true;
}

function openDropdown() {
	document.getElementById("myDropdown").classList.toggle("show");
	}

// Close the dropdown if the user clicks outside of it
window.onclick = function(event) {
  if (!event.target.matches('.dropbtn')) {
    var dropdowns = document.getElementsByClassName("dropdown-content");
    var i;
    for (i = 0; i < dropdowns.length; i++) {
      var openDropdown = dropdowns[i];
      if (openDropdown.classList.contains('show')) {
        openDropdown.classList.remove('show');
      }
    }
  }
}
$('#alphabet_sorter_asc').click(function() {
	  $('.wrapper .item').sort(function(a, b) {
	    return $(a).data('name').localeCompare($(b).data('name'));
	  }).appendTo('.wrapper');
	});
$('#alphabet_sorter_desc').click(function() {
	  $('.wrapper .item').sort(function(a, b) {
		 return $(b).data('name').localeCompare($(a).data('name'));
	  }).appendTo('.wrapper');
	});
$('#rating_desc').click(function() {
	  $('.wrapper .item').sort(function(a, b) {
	    return $(b).data('rating') - $(a).data('rating');
	  }).appendTo('.wrapper');
	});
$('#rating_asc').click(function() {
	  $('.wrapper .item').sort(function(a, b) {
	    return $(a).data('rating') - $(b).data('rating');
	  }).appendTo('.wrapper');
	});
$('#recent_desc').click(function() {
	  $('.wrapper .item').sort(function(a, b) {
	    return $(a).data('id') - $(b).data('id');
	  }).appendTo('.wrapper');
	});
$('#recent_asc').click(function() {
	  $('.wrapper .item').sort(function(a, b) {
	    return $(b).data('id') - $(a).data('id');
	  }).appendTo('.wrapper');
	});

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
</body>
</html>