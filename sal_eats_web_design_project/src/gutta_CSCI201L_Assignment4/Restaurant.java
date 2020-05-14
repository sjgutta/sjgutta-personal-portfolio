package gutta_CSCI201L_Assignment4;

public class Restaurant {
	public String name;
	public String address;
	public String phone_number;
	public String cuisine;
	public String price;
	public String page_link;
	public String image_link;
	public int rating;
	public String yelp_id;
	
	Restaurant(String name, String address, String phone_number, String cuisine, String price,
			String page_link, String image_link, int rating, String yelp_id){
		this.name = name;
		this.address = address;
		this.phone_number = phone_number;
		this.cuisine = cuisine;
		this.price = price;
		this.image_link = image_link;
		this.page_link = page_link;
		this.rating = rating;
		this.yelp_id = yelp_id;
	}
	
	public void print_info() {
		System.out.println(this.name);
		System.out.println(this.address);
		System.out.println(this.phone_number);
		System.out.println(this.cuisine);
		System.out.println(this.price);
		System.out.println(this.page_link);
		System.out.println(this.image_link);
		System.out.println(this.rating);
		System.out.println(this.yelp_id);
	}
}
