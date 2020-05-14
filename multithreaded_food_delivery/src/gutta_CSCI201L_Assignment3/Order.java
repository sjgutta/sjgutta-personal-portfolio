package gutta_CSCI201L_Assignment3;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

public class Order {
	public String API_KEY = "EROtvMU3rXL7J5M8NdWuV3aPRnd7EwmquK_SmRmOEyKzpN0hwT-Z1U"
			+ "tzSHlX_9jPgqCu1shWNraXpgHsfm2bb-vBID-Bh5MnxpwkS-zWy78tXuu3AssYCNPKSuZzXnYx";
	int time;
	String restaurant_name;
	String food_item;
	double longitude;
	double latitude;
	Order(int time, String restaurant_name, String food_item){
		this.time = time;
		this.restaurant_name = restaurant_name;
		this.food_item = food_item;
	}
	
	public double distanceFrom(double current_lat, double current_long) {
		//calculate distance between inputs and this order's location
		double latr1 = (double) Math.toRadians(this.latitude);
		double longr1 = (double) Math.toRadians(this.longitude);
		double latr2 = (double) Math.toRadians(current_lat);
		double longr2 = (double) Math.toRadians(current_long);
		double result = (double) (3963.0 * Math.acos((Math.sin(latr1) * Math.sin(latr2)) + 
				Math.cos(latr1) * Math.cos(latr2) * Math.cos(longr2 - longr1)));
		return (double) (Math.round(result*10)/10.0);
	}
	
	//searching for the restaurant for this order in yelp to properly store location it needs to deliver to
	public void searchYelp(double hq_lat, double hq_long) {
		//This function will search yelp and find the proper location for this order
		URL url;
		String content = "";
		try {
			String encoded_name = this.restaurant_name.replace(" ", "%20");
			url = new URL("https://api.yelp.com/v3/businesses/search?term=" + encoded_name + 
					"&latitude=" + hq_lat + "&longitude=" + hq_long);
			HttpURLConnection con = (HttpURLConnection) url.openConnection();
			con.setRequestMethod("GET");
			con.setRequestProperty("authorization", "Bearer " + this.API_KEY);
			BufferedReader in = new BufferedReader(
			new InputStreamReader(con.getInputStream()));
			String inputLine;
			while ((inputLine = in.readLine()) != null) {
			    content = content.concat(inputLine);
			}
			in.close();
			con.disconnect();
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		JsonObject jobj = new Gson().fromJson(content, JsonObject.class);
		JsonArray businesses = jobj.get("businesses").getAsJsonArray();
		JsonObject jobj2 = businesses.get(0).getAsJsonObject();
		JsonObject coordinates = jobj2.get("coordinates").getAsJsonObject();
		double latitude = coordinates.get("latitude").getAsDouble();
		double longitude = coordinates.get("longitude").getAsDouble();
		this.latitude = latitude;
		this.longitude = longitude;
	}
}
