<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<style>
div.backdrop {
  position: absolute;
  display: none;
  background-color: black;
  opacity: 65%;
  top: 0;
  left: 0;
  height: 100%;
  width: 100%; z-index: 2;
} 

div.absolute {
  position: absolute;
  margin-left: auto; margin-bottom: auto;
  margin-right: auto; margin-top: auto;
  left: 0; top: 0;
  right: 0; bottom: 0;
  width: 50vw; opacity: 100%;
  height: 40vh;
  z-index: 3;
}
</style>
</head>
<body>


<p id="demo">Click the button to get your position.</p>
<p id="latclicked"></p>
<p id="longclicked"></p>
<button onclick="getLocation()">Try It</button>

<div class="backdrop" id="backdrop">
<div class="absolute" id="mapholder"></div>
</div>

<script src="https://maps.google.com/maps/api/js?key=AIzaSyCeUx0QZX-im176JC0eFqAq0qrXtQ9u8jI"></script>
<!--
To use this code on your website, get a free API key from Google.
Read more at: https://www.w3schools.com/graphics/google_maps_basic.asp
-->
<script>
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
  mapholder.style.height = '250px';
  mapholder.style.width = '500px';

  var myOptions = {
    center:latlon,zoom:14,
    mapTypeId:google.maps.MapTypeId.ROADMAP,
    mapTypeControl:false,
    navigationControlOptions:{style:google.maps.NavigationControlStyle.SMALL}
  }
    
  var map = new google.maps.Map(document.getElementById("mapholder"), myOptions);
  document.getElementById("backdrop").style.display = "block";
  google.maps.event.addListener(map,'click',function(event) {               
	      document.getElementById('latclicked').innerHTML = event.latLng.lat();
	      document.getElementById('longclicked').innerHTML =  event.latLng.lng();
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
