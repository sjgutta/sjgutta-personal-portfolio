package gutta_CSCI201L_Assignment3;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;


public class Driver extends Thread{
	private BufferedReader br;
	private PrintWriter pw;
	
	public Driver(String hostname, int port) {
		try {
			Socket s = new Socket(hostname, port);
			br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			pw = new PrintWriter(s.getOutputStream());
			this.start();
		} catch (IOException ioe) {
			System.out.println("ioe in Driver constructor: " + ioe.getMessage());
		}
	}
	
	public void run() {
		try {
			while(true) {
				String line = br.readLine();
				if(line==null) {
					continue;
				}
				System.out.println(line);
			}
		} catch (IOException ioe) {
			System.out.println("ioe in ChatClient.run(): " + ioe.getMessage());
		}
	}
	
	public static void main(String [] args) {
		Scanner inputReader = new Scanner(System.in);
		System.out.println("Welcome to SalEats v2.0!");
		System.out.print("Enter the server hostname: ");
		String hostname = inputReader.nextLine();
		System.out.print("Enter the server port: ");
		int port = inputReader.nextInt();
		Driver dr = new Driver(hostname, port);
		inputReader.close();
	}
}
