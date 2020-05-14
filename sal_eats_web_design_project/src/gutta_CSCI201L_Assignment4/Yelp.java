package gutta_CSCI201L_Assignment4;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

public class Yelp {
	public static String API_KEY = "EROtvMU3rXL7J5M8NdWuV3aPRnd7EwmquK_SmRmOEyKzpN0hwT-Z1U"
			+ "tzSHlX_9jPgqCu1shWNraXpgHsfm2bb-vBID-Bh5MnxpwkS-zWy78tXuu3AssYCNPKSuZzXnYx";
	
	//search by user inputs in website search
	public static ArrayList<Restaurant> searchYelp(double hq_lat, double hq_long, String name, String sort_value) {
		//This function will search yelp and find the proper location for this order
		URL url;
		String content = "";
		try {
			String encoded_name = name.replace(" ", "%20");
			String url_string = "https://api.yelp.com/v3/businesses/search?term=" + encoded_name + "&latitude=" + hq_lat +
					"&longitude=" + hq_long + "&sort_by=" + sort_value;
			System.out.println(url_string);
			url = new URL(url_string);
			HttpURLConnection con = (HttpURLConnection) url.openConnection();
			con.setRequestMethod("GET");
			con.setRequestProperty("authorization", "Bearer " + Yelp.API_KEY);
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

		
		//creating array of restaurant objects to return
		ArrayList<Restaurant> temp_results = new ArrayList<Restaurant>();
		ArrayList<Restaurant> results = new ArrayList<Restaurant>();
		for(int i=0; i<businesses.size(); i++) {
			try {
				JsonObject jobj2 = businesses.get(i).getAsJsonObject();
				String new_name = jobj2.get("name").getAsString();
				System.out.println(new_name);
				String page_link = jobj2.get("url").getAsString();
				
				page_link = page_link.substring(0,page_link.lastIndexOf('?'));
				
				String image_link = jobj2.get("image_url").getAsString();
				
				//building address string
				JsonObject add_object = jobj2.get("location").getAsJsonObject();
				String address = add_object.get("address1").getAsString() + " " + add_object.get("city").getAsString() + ", ";
				address = address.concat(add_object.get("state").getAsString() + " " + add_object.get("zip_code").getAsString());
				
				String phone_number = jobj2.get("display_phone").getAsString();
				
				String price = jobj2.get("price").getAsString();
				
				String yelp_id = jobj2.get("id").getAsString();
				
				int rating = jobj2.get("rating").getAsInt();
				
				JsonArray categories = jobj2.get("categories").getAsJsonArray();
				String cuisine = "";
				for(int j=0; j<categories.size() - 1; j++) {
					JsonObject cat = categories.get(j).getAsJsonObject();
					cuisine = cuisine.concat(cat.get("title").getAsString() + ", ");
				}
				JsonObject cat = categories.get(categories.size()-1).getAsJsonObject();
				cuisine = cuisine.concat(cat.get("title").getAsString());
				
				Restaurant new_restaurant = new Restaurant(new_name, address, phone_number, cuisine, price, page_link, image_link, rating, yelp_id);
				temp_results.add(new_restaurant);
			} catch (Exception e) {
				continue;
			}
		}
		if(temp_results.size()>=10) {
			for(int i=0; i<10; i++) {
				results.add(temp_results.get(i));
			}
		}else {
			for(int i=0; i<temp_results.size(); i++) {
				results.add(temp_results.get(i));
			}
		}
		return results;
		
	}
	
	//search by unique yelp id and get the restaurant
	public static Restaurant search_yelp_by_id(String id) {
		//This function will search yelp and find the proper location for this order
		URL url;
		String content = "";
		try {
			String url_string = "https://api.yelp.com/v3/businesses/" + id;
			url = new URL(url_string);
			HttpURLConnection con = (HttpURLConnection) url.openConnection();
			con.setRequestMethod("GET");
			con.setRequestProperty("authorization", "Bearer " + Yelp.API_KEY);
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
		JsonObject jobj2 = new Gson().fromJson(content, JsonObject.class);

		
		//creating array of restaurant objects to return
		try {
			String new_name = jobj2.get("name").getAsString();
			String page_link = jobj2.get("url").getAsString();
			
			page_link = page_link.substring(0,page_link.lastIndexOf('?'));
			
			String image_link = jobj2.get("image_url").getAsString();
			
			//building address string
			JsonObject add_object = jobj2.get("location").getAsJsonObject();
			String address = add_object.get("address1").getAsString() + " " + add_object.get("city").getAsString() + ", ";
			address = address.concat(add_object.get("state").getAsString() + " " + add_object.get("zip_code").getAsString());
			
			String phone_number = jobj2.get("display_phone").getAsString();
			
			String price = jobj2.get("price").getAsString();
			
			String yelp_id = jobj2.get("id").getAsString();
			
			int rating = jobj2.get("rating").getAsInt();
			
			JsonArray categories = jobj2.get("categories").getAsJsonArray();
			String cuisine = "";
			for(int j=0; j<categories.size() - 1; j++) {
				JsonObject cat = categories.get(j).getAsJsonObject();
				cuisine = cuisine.concat(cat.get("title").getAsString() + ", ");
			}
			JsonObject cat = categories.get(categories.size()-1).getAsJsonObject();
			cuisine = cuisine.concat(cat.get("title").getAsString());
			
			Restaurant new_restaurant = new Restaurant(new_name, address, phone_number, 
					cuisine, price, page_link, image_link, rating, yelp_id);
			return new_restaurant;
		} catch (NullPointerException e) {
			Restaurant new_restaurant = new Restaurant("error", "error", "error", "error", "error", "error", "error", 0, "error");
			return new_restaurant;
		}
	}
}
