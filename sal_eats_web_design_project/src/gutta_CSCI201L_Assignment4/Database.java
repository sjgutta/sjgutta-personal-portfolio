package gutta_CSCI201L_Assignment4;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.TimeZone;



public class Database {
	public static Connection getConnection() {
		try {
			DriverManager.registerDriver(new com.mysql.jdbc.Driver ());
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Connection conn = null;
		try {
			Calendar now = Calendar.getInstance();
		    TimeZone timeZone = now.getTimeZone();
		    String password = "INSERT YOURS HERE";
			String conn_string = "jdbc:mysql://localhost/sal_eats?user=root&password=" + password + "&serverTimezone=" + timeZone.getID();
			conn = DriverManager.getConnection(conn_string);
		} catch (SQLException sqle) {
			System.out.println ("SQLException: " + sqle.getMessage());
		} /*finally {
			try {
				if (conn != null) {
					conn.close();
				}
			} catch (SQLException sqle) {
				System.out.println("sqle: " + sqle.getMessage());
			}
		}*/
		return conn;
	}
	
	public static void insertUser(String username, String email, String password) {
		if(!Database.verifyUserNotExists(username)) {
			System.out.println("User already exists");
			return;
		}
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		try {
			ps = conn.prepareStatement("INSERT INTO users (username, email, password) VALUES (?, ?, ?)");
			ps.setString(1, username);
			ps.setString(2, email);
			ps.setString(3, password);
			ps.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static int getUserID(String username, String password) {
		String hashed_password = Database.generateHash(password);
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		try {
			ps = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
			ps.setString(1, username);
			ps.setString(2, hashed_password);
			rs = ps.executeQuery();
			if(rs.next()!=false) {
				int id = rs.getInt("user_id");
				return id;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return 0;
	}
	
	public static String getUsername(int user_id) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		try {
			ps = conn.prepareStatement("SELECT * FROM users WHERE user_id=?");
			ps.setInt(1, user_id);
			rs = ps.executeQuery();
			if(rs.next()!=false) {
				String username = rs.getString("username");
				return username;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return "";
	}
	
	public static boolean verifyUserNotExists(String username) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		try {
			ps = conn.prepareStatement("SELECT * FROM users WHERE username=?");
			ps.setString(1, username);
			rs = ps.executeQuery();
			if(rs.next()==false) {
				return true;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return false;
	}
	
	public static boolean googleUserExists(String username) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		try {
			ps = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
			ps.setString(1, username);
			ps.setString(2, "google");
			rs = ps.executeQuery();
			if(rs.next()==false) {
				return false;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return true;
	}
	
	public static int getGoogleUserID(String username) {
		String hashed_password = Database.generateHash("google");
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		try {
			ps = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
			ps.setString(1, username);
			ps.setString(2, hashed_password);
			rs = ps.executeQuery();
			if(rs.next()!=false) {
				int id = rs.getInt("user_id");
				return id;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return 0;
	}
	
	//used for hashing user passwords
	public static String generateHash(String unhashed_password) {
		try { 
            // Static getInstance method is called with hashing MD5 
            MessageDigest md = MessageDigest.getInstance("MD5"); 
            byte[] messageDigest = md.digest(unhashed_password.getBytes());  
            BigInteger no = new BigInteger(1, messageDigest); 
            // Convert message digest into hex value 
            String hashtext = no.toString(16); 
            while (hashtext.length() < 32) { 
                hashtext = "0" + hashtext; 
            }
            return hashtext; 
        }catch (NoSuchAlgorithmException e) { 
            throw new RuntimeException(e); 
        }
	}
	
	public static boolean authenticateUser(String username, String password) {
		String hashed_password = Database.generateHash(password);
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		try {
			ps = conn.prepareStatement("SELECT * FROM users WHERE username=?");
			ps.setString(1, username);
			rs = ps.executeQuery();
			if(rs.next()==false) {
				//user does not exist
				return false;
			}
			if(rs.getString("password").equals(hashed_password)) {
				return true;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return false;
	}
	
	public static void newFavorite(int user_id, String yelp_id) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		if(!Database.already_favorite(user_id, yelp_id)) {
			try {
				ps = conn.prepareStatement("INSERT INTO favorites (user, yelp_id) VALUES (?, ?)");
				ps.setInt(1, user_id);
				ps.setString(2, yelp_id);
				ps.executeUpdate();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public static boolean already_favorite(int user_id, String yelp_id) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		try {
			ps = conn.prepareStatement("SELECT * FROM favorites WHERE user=? AND yelp_id=?");
			ps.setInt(1, user_id);
			ps.setString(2, yelp_id);
			rs = ps.executeQuery();
			if(rs.next()==false) {
				return false;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return true;
	}
	
	public static void removeFavorite(int user_id, String yelp_id) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		if(Database.already_favorite(user_id, yelp_id)) {
			try {
				ps = conn.prepareStatement("DELETE FROM favorites WHERE user=? AND yelp_id=?");
				ps.setInt(1, user_id);
				ps.setString(2, yelp_id);
				System.out.println("Removing user of " + Integer.toString(user_id) + " and yelp id of " + yelp_id);
				ps.executeUpdate();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public static ArrayList<Restaurant> getFavorites(int user_id){
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		ArrayList<Restaurant> result = new ArrayList<Restaurant>();
		try {
			ps = conn.prepareStatement("SELECT * FROM favorites WHERE user=?");
			ps.setInt(1, user_id);
			rs = ps.executeQuery();
			while(rs.next()) {
				String yelp_id = rs.getString("yelp_id");
				Restaurant new_restaurant = Yelp.search_yelp_by_id(yelp_id);
				result.add(new_restaurant);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return result;
	}
	
	public static ArrayList<Integer> getFavoriteIds(int user_id){
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		ArrayList<Integer> ids = new ArrayList<Integer>();
		try {
			ps = conn.prepareStatement("SELECT * FROM favorites WHERE user=?");
			ps.setInt(1, user_id);
			rs = ps.executeQuery();
			while(rs.next()) {
				Integer id = rs.getInt("favorite_id");
				ids.add(id);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return ids;
	}
}
