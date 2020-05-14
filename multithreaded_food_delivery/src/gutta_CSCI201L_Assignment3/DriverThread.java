package gutta_CSCI201L_Assignment3;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Vector;

public class DriverThread extends Thread{
	
	private PrintWriter pw;
	private BufferedReader br;
	private HQ hq;
	private boolean finished = false;
	private Vector<Order> current_orders = new Vector<Order>();
	double current_lat;
	double current_long;
	double hq_lat, hq_long;
	public DriverThread(Socket s, HQ hq) {
		try {
			this.hq = hq;
			pw = new PrintWriter(s.getOutputStream());
			br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			this.start();
		} catch (IOException ioe) {
			System.out.println("ioe in DriverThread constructor: " + ioe.getMessage());
		}
	}
	
	public void sendMessage(String message) {
		pw.println(message);
		pw.flush();
	}
	
	public void sendStampedMessage(String message) {
		String time_string = this.currentTime();
		pw.println(time_string + " " + message);
		pw.flush();
	}
	
	public String currentTime() {
		Date date = new Date();
		String formatted = new SimpleDateFormat("[mm:ss.SSS").format(date.getTime());
		
		if(formatted.length() <= 13) {
			formatted = formatted.concat("0");
		}
		formatted = formatted.substring(0, formatted.length()-1).concat("]");
		return formatted;
	}
	
	public void run() {
		while(!finished) {
			if(!this.current_orders.isEmpty()) {
				long current_sleep_time;
				Order current_order = current_orders.get(0);
				for(Order order: current_orders) {
					String message = "Starting delivery of " + order.food_item + " to " + order.restaurant_name + ".";
					this.sendStampedMessage(message);
				}
				while(!this.current_orders.isEmpty()) {
					int minIndex = DriverThread.findSmallestIndex(current_orders, current_lat, current_long);
					current_sleep_time = (long) (1000* current_orders.get(minIndex).distanceFrom(current_lat, current_long));
					current_order = current_orders.get(minIndex);
					this.current_lat = current_order.latitude;
					this.current_long = current_order.longitude;
					this.current_orders.remove(minIndex);
					try {
						Thread.sleep(current_sleep_time);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					String message = "Finished delivery of " + current_order.food_item + " to " + current_order.restaurant_name + ".";
					this.sendStampedMessage(message);
					if(!current_orders.isEmpty()) {
						for(Order order: current_orders) {
							if(order.restaurant_name.equals(current_order.restaurant_name)) {
								message = "Finished delivery of " + order.food_item + " to " + order.restaurant_name + ".";
								this.sendStampedMessage(message);
								current_orders.remove(order);
								if(current_orders.isEmpty()) {
									break;
								}
							}
						}
					}
					if(!this.current_orders.isEmpty()) {
						int next_order_index = DriverThread.findSmallestIndex(current_orders, this.current_lat, this.current_long);
						Order next_order = this.current_orders.get(next_order_index);
						this.sendStampedMessage("Continuing delivery to " + next_order.restaurant_name + ".");
					}
				}
				long return_sleep_time = (long)(1000 * current_order.distanceFrom(hq_lat, hq_long));
				this.sendStampedMessage("Finished all deliveries, returning back to HQ");
				try {
					Thread.sleep(return_sleep_time);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				this.sendStampedMessage("Returned to HQ");
				this.hq.addReadyDriver(this);
			}
		}
	}
	
	public void makeTrip(Vector<Order> current_orders, double hq_lat, double hq_long) {
		this.current_orders = current_orders;
		this.current_lat = hq_lat;
		this.current_long = hq_long;
		this.hq_lat = hq_lat;
		this.hq_long = hq_long;
	}
	
	public static int findSmallestIndex(Vector<Order> current_orders, double hq_lat, double hq_long) {
		int minIndex = 0;
		double minDistance;
		if(current_orders.size()==1) {
			return 0;
		}
		minDistance = current_orders.get(0).distanceFrom(hq_lat, hq_long);
		for(int i=1; i<current_orders.size(); i++) {
			if(current_orders.get(i).distanceFrom(hq_lat, hq_long)<minDistance) {
				minIndex = i;
			}
		}
		return minIndex;
	}
}
