package gutta_CSCI201L_Assignment3;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.Vector;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class HQ {
	public Vector<Order> orderList;
	private Vector<DriverThread> driverThreads;
	private int total_drivers;
	public Vector<Order> ready_orders = new Vector<Order>();
	public Vector<DriverThread> ready_drivers = new Vector<DriverThread>();
	Lock lock = new ReentrantLock();
	public Condition driverAvailable = lock.newCondition();
	public double hq_lat, hq_long;
	public HQ(int port, int drivers, Vector<Order> orderList, double latitude, double longitude) {
		try {
			ServerSocket ss = new ServerSocket(port);
			System.out.println("\nListening on port " + port + ". Waiting for drivers...\n");
			this.driverThreads = new Vector<DriverThread>();
			this.total_drivers = drivers;
			this.orderList = orderList;
			this.hq_lat = latitude;
			this.hq_long = longitude;
			while(true) {
				Socket s = ss.accept(); // blocking
				System.out.println("Connection from: " + s.getInetAddress());
				DriverThread dt = new DriverThread(s, this);
				driverThreads.add(dt);
				this.ready_drivers.add(dt);
				if(driverThreads.size()<total_drivers) {
					int num_needed = total_drivers - driverThreads.size();
					System.out.println("Waiting for " + num_needed + " more driver(s)...\n");
					this.broadcast(num_needed + " more driver is needed before the service can begin.\n" + 
							"Waiting...\n");
				}else {
					this.broadcast("All drivers have arrived! Starting service.");
					System.out.println("Starting Service\n");
					break;
				}
			}
		} catch (IOException ioe) {
			System.out.println("ioe in HQ constructor: " + ioe.getMessage());
		}
		for(Order order: this.orderList) {
			order.searchYelp(this.hq_lat, this.hq_long);
		}
		for(Order order : this.orderList) {
			if(order.time != 0) {
				OrderThread order_thread = new OrderThread(order, this.ready_orders);
				//trying to avoid timing issues where the order doesn't join ready list on time
				order_thread.setPriority(10);
				order_thread.start();
			}else {
				this.ready_orders.add(order);
			}
		}
		int orders_completed = 0;
		while(orders_completed<this.orderList.size()) {
			/*if(this.ready_drivers.isEmpty()) {
				try {
					this.driverAvailable.await();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}*/
			if(!this.ready_orders.isEmpty() && !this.ready_drivers.isEmpty()) {
				/*for(Order order : this.orderList) {
					System.out.print(order.restaurant_name + ", " + order.food_item + " | ");
				}*/
				//System.out.println("");
				//dispatch orders to drivers here
				lock.lock();
				//System.out.println(orders_completed + "+" + this.ready_orders.size());
				//System.out.println(this.ready_orders);
				DriverThread dispatching = this.ready_drivers.remove(0);
				Vector<Order> new_trip_vector = new Vector<Order>(this.ready_orders);
				orders_completed += new_trip_vector.size();
				dispatching.makeTrip(new_trip_vector, hq_lat, hq_long);
				this.ready_orders.clear();
				lock.unlock();
			}
		}
		while(true) {
			if(this.ready_drivers.size()==total_drivers) {
				//don't let program say all orders complete until cars are back to hq
				break;
			}
		}
		System.out.println("All orders completed!");
		for(DriverThread dt: this.driverThreads) {
			dt.sendStampedMessage("All orders completed!");
		}
	}
	
	public void broadcast(String message) {
		if (message != null) {
			for(DriverThread threads : driverThreads) {
				threads.sendMessage(message);
			}
		}
	}
	
	public void addReadyDriver(DriverThread dr) {
		this.ready_drivers.add(dr);
		//this.driverAvailable.signal();
	}
	
	public static void main(String [] args) {
		Scanner inputReader = new Scanner(System.in);
		Vector<Order> orderList = new Vector<Order>();
		while(true) {
	    	System.out.print("What is the name of the file containing the schedule information? ");
			String filename = inputReader.nextLine();
		    try {
				FileReader fr2 = new FileReader(filename);
				BufferedReader br = new BufferedReader(fr2);
				String line = br.readLine();
				while(line!=null) {
					String[] parts = line.split(", ");
					if(parts.length!=3) {
						throw new Exception("");
					}
					Order order = new Order(Integer.parseInt(parts[0]), parts[1], parts[2]);
					orderList.add(order);
					line = br.readLine();
				}
				br.close();
				break;
			} catch (FileNotFoundException fnfe) {
				System.out.println("That file does not exist.");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				System.out.println("An IO error occurred when reading from " + filename);
			} catch(Exception e) {
				System.out.println("The file is not properly formatted.");
			}
	    }
		double latitude;
	    double longitude;
	    while(true) {	
	    	try {
	    		System.out.print("What is your latitude? ");
			    try{
			    	latitude = inputReader.nextDouble();
			    }catch(Exception e) {
			    	throw new Exception("error");
			    }
			    if(latitude<-90 || latitude > 90) {
			    	System.out.println("The latitude is not in the valid range.");
			    	throw new RuntimeException("error");
			    }
			    break;
	    	}catch(RuntimeException e){
	    		continue;
	    	}catch(Exception e) {
	    		System.out.println("Your input is not valid type for latitude. It must be a double.");
	    		inputReader.nextLine();
	    		continue;
	    	}
	    }
	    while(true) {
	    	try {
	    		inputReader.nextLine();
	    		System.out.print("What is your longitude? ");
			    try{
			    	longitude = inputReader.nextDouble();
			    }catch(Exception e) {
			    	throw new Exception("error");
			    }
			    if(longitude<-180 || longitude > 180) {
			    	System.out.println("The longitude is not in the valid range.");
			    	throw new RuntimeException("error");
			    }
			    break;
	    	}catch(RuntimeException e){
	    		continue;
	    	}catch(Exception e) {
	    		System.out.println("Your input is not valid type for longitude. It must be a double.");
	    		continue;
	    	}
	    }
	    int num_drivers;
	    while(true) {
	    	try {
	    		inputReader.nextLine();
	    		System.out.print("How many drivers will be in service today? ");
			    try{
			    	num_drivers = inputReader.nextInt();
			    }catch(Exception e) {
			    	throw new Exception("error");
			    }
			    if(num_drivers<1) {
			    	System.out.println("There must be at least 1 driver.");
			    	throw new RuntimeException("error");
			    }
			    break;
	    	}catch(RuntimeException e){
	    		continue;
	    	}catch(Exception e) {
	    		System.out.println("Your input is not valid type for number of drivers. It must be an integer.");
	    		continue;
	    	}
	    }
		inputReader.close();
		HQ hq = new HQ(3456, num_drivers, orderList, latitude, longitude);
	}
}