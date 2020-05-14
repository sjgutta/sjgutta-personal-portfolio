package final_project;

import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Time;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.TimeZone;

import com.google.gson.*;
//import java.sql.Statement;

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
			String conn_string = "jdbc:mysql://schedget-db.cmvyd0ufn9eh.us-west-1.rds.amazonaws.com/schedget?user=admin&password=SchedgetAdmin*01&serverTimezone=" + timeZone.getID();
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
	
	public static int getUserID(String username) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		int user_id = 0;
		try {
			ps = conn.prepareStatement("SELECT * FROM users WHERE username=?");
			ps.setString(1, username);
			rs = ps.executeQuery();
			rs.next();
			user_id = rs.getInt("user_id");
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return user_id;
	}
	
	public static void insert_schedule(int user_id, String new_schedule_json) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		try {
			ps = conn.prepareStatement("INSERT INTO schedules (user, schedule_data) VALUES (?, ?)");
			ps.setString(2, new_schedule_json);
			ps.setInt(1, user_id);
			ps.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void delete_schedule(int user_id, String deleting_schedule_json) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		try {
			ps = conn.prepareStatement("DELETE FROM schedules WHERE user=? AND schedule_data=?");
			ps.setString(2, deleting_schedule_json);
			ps.setInt(1, user_id);
			ps.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void delete_schedule(int user_id, int schedID) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		try {
			ps = conn.prepareStatement("DELETE FROM schedules WHERE user=? AND schedule_id=?");
			ps.setInt(2, schedID);
			ps.setInt(1, user_id);
			ps.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static ArrayList<Schedule> get_user_schedules(int user_id) {
		ArrayList<Schedule> results = new ArrayList<Schedule>();
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		Gson gson = new Gson();
		try {
			ps = conn.prepareStatement("SELECT * FROM schedules WHERE user=?");
			ps.setString(1, Integer.toString(user_id));
			rs = ps.executeQuery();
			while(rs.next()) {
				String json_string = rs.getString("schedule_data");
				String schedID = rs.getString("schedule_id");
				if(json_string!=null) {
					Schedule new_schedule = gson.fromJson(json_string, Schedule.class);
					results.add(new_schedule);
					new_schedule.add_schedule_id(schedID);
				}
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return results;
	}
	
	public static ArrayList<Reservation> get_room_reservations(int room_id){
		ArrayList<Reservation> results = new ArrayList<Reservation>();
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		Gson gson = new Gson();
		try {
			ps = conn.prepareStatement("SELECT * FROM reservations WHERE study_room=?");
			ps.setString(1, Integer.toString(room_id));
			rs = ps.executeQuery();
			while(rs.next()) {
				int user = rs.getInt("user");
				int study_room = rs.getInt("study_room");
				Time start_time = rs.getTime("start_time");
				Time end_time = rs.getTime("end_time");
				Date reservation_date = rs.getDate("reservation_date");
				//create new reservation and add
				Reservation new_reservation = new Reservation(user, study_room, 
						start_time, end_time, reservation_date);
				results.add(new_reservation);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return results;
	}
	
	public static void insert_reservation(Reservation new_reservation) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		try {
			ps = conn.prepareStatement("INSERT INTO reservations (user, study_room, start_time, end_time, reservation_date) VALUES (?, ?, ?, ?, ?)");
			ps.setInt(1, new_reservation.user);
			ps.setInt(2, new_reservation.room);
			ps.setTime(3, new_reservation.start_time);
			ps.setTime(4, new_reservation.end_time);
			ps.setDate(5,  new_reservation.reservation_date);
			ps.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static ArrayList<Course> get_course(String search_prefix, String search_code){
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		ResultSet rs;
		ArrayList<Course> result = new ArrayList<Course>();
		try {
			ps = conn.prepareStatement("SELECT * FROM courses WHERE prefix=? AND code=?");
			ps.setString(1, search_prefix);
			ps.setString(2, search_code);
			rs = ps.executeQuery();
			while(rs.next()) {
				String prefix = rs.getString("prefix");
				String code = rs.getString("code");
				String professor_name = rs.getString("professor_name");
				String classroom = rs.getString("classroom");
				String days = rs.getString("days");
				Time start_time = rs.getTime("start_time");
				Time end_time = rs.getTime("end_time");
				String course_type = rs.getString("course_type");
				Course new_course = new Course(prefix, code, professor_name, classroom, days, start_time, end_time, course_type);
				result.add(new_course);
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return result;
	}
	
	public static void insert_course(String prefix, String code, String professor_name, String classroom, String days, Time start_time,
			Time end_time, String course_type) {
		Connection conn = Database.getConnection();
		PreparedStatement ps;
		try {
			ps = conn.prepareStatement("Insert INTO courses (prefix, code, professor_name, classroom, days, start_time, end_time, course_type) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
			ps.setString(1, prefix);
			ps.setString(2, code);
			ps.setString(3, professor_name);
			ps.setString(4, classroom);
			ps.setString(5, days);
			ps.setTime(6, start_time);
			ps.setTime(7, end_time);
			ps.setString(8, course_type);
			ps.executeUpdate();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	//function to convert scraper time string to time object
	public static Time parse_time_string_start(String time_string) {
		String[] parts = time_string.split(":");
		String am_or_pm = parts[3].substring(2, 4);
		if(am_or_pm.equals("pm")) {
			int current_start_hours = Integer.parseInt(parts[0]);
			int current_end_hours = Integer.parseInt(parts[2]);
			if(current_end_hours > current_start_hours && current_end_hours < 12) {
				current_start_hours +=12;
			}
			if(current_start_hours < 10) {
				parts[0] = "0" + Integer.toString(current_start_hours);
			}else {
				parts[0] = Integer.toString(current_start_hours);
			}
			
		}else {
			int current_start_hours = Integer.parseInt(parts[0]);
			if(current_start_hours < 10) {
				parts[0] = "0" + parts[0];
			}
		}
		time_string = parts[0] + ":" + parts[1];
		LocalTime localtime = LocalTime.parse(time_string);
		Time result = Time.valueOf(localtime);
		return result;
	}
	
	//function to convert scraper time string in time object but for end time
	public static Time parse_time_string_end(String time_string) {
		String[] parts = time_string.split(":");
		String am_or_pm = parts[3].substring(2, 4);
		if(am_or_pm.equals("pm")) {
			int current_end_hours = Integer.parseInt(parts[2]);
			if(current_end_hours<12) {
				current_end_hours += 12;
			}
			parts[2] = Integer.toString(current_end_hours);
			
		}else {
			int current_end_hours = Integer.parseInt(parts[2]);
			if(current_end_hours < 10) {
				parts[2] = "0" + parts[2];
			}
		}
		time_string = parts[2] + ":" + parts[3].substring(0,2);
		LocalTime localtime = LocalTime.parse(time_string);
		Time result = Time.valueOf(localtime);
		return result;
	}
	
	//helper function used when running scraper
	//converts scraped days string into format for database
	public static String parse_days_string(String day_string) {
		String result = "";
		if(day_string == "MWF") {
			result = "M,W,F";
			return result;
		}else if(day_string.equals("Monday")) {
			result = "M";
			return result;
		}else if(day_string.equals("Tuesday")) {
			result = "T";
			return result;
		}else if(day_string.equals("Wednesday")) {
			result = "W";
			return result;
		}else if(day_string.equals("Thursday")) {
			result = "TH";
			return result;
		}else if(day_string.equals("Friday")) {
			result = "F";
			return result;
		}else {
			String[] parts = day_string.split(", ");
			if(parts.length == 2) {
				if(parts[0].equals("Mon")) {
					result = result + "M,";
				}else if(parts[0].equals("Tue")) {
					result = result + "T,";
				}else if(parts[0].equals("Wed")) {
					result = result + "W,";
				}else if(parts[0].equals("Thu")) {
					result = result + "TH,";
				}else if(parts[0].equals("Fri")) {
					result = result + "F,";
				}
			}else {
				for(int i=0; i < parts.length - 1; i++) {
					if(parts[i].equals("Mon")) {
						result = result + "M,";
					}else if(parts[i].equals("Tue")) {
						result = result + "T,";
					}else if(parts[i].equals("Wed")) {
						result = result + "W,";
					}else if(parts[i].equals("Thu")) {
						result = result + "TH,";
					}else if(parts[i].equals("Fri")) {
						result = result + "F,";
					}
				}
			}
			String last_day = parts[parts.length - 1];
			if(last_day.equals("Mon")) {
				result = result + "M";
			}else if(last_day.equals("Tue")) {
				result = result + "T";
			}else if(last_day.equals("Wed")) {
				result = result + "W";
			}else if(last_day.equals("Thu")) {
				result = result + "TH";
			}else if(last_day.equals("Fri")) {
				result = result + "F";
			}
			return result;
		}
	}
	
	//function to parse out the prefix from scraped class
	public static String isolate_prefix(String scraped_string) {
		int code_start = 0;
		for(int i=0; i<scraped_string.length(); i++) {
			if(Character.isDigit(scraped_string.charAt(i))) {
				code_start = i;
				break;
			}
		}
		return scraped_string.substring(0, code_start);
	}
	
	//function to parse out the class code from scraped class
	public static String isolate_code(String scraped_string) {
		int code_start = 0;
		for(int i=0; i<scraped_string.length(); i++) {
			if(Character.isDigit(scraped_string.charAt(i))) {
				code_start = i;
				break;
			}
		}
		return scraped_string.substring(code_start, scraped_string.length());
	}
	
	public static void main(String[] args) {
		//Database.insert_course("BUAD", "304", "Townsend", "JFF 322", "M,W", start, end, "Lecture");
		ArrayList<Course> courses = Database.get_course("CSCI", "201");
		for(Course course: courses) {
			course.print_course();
		}
		/*
		ArrayList<Course> courses_2 = Database.get_course("CSCI", "170");
		for(Course course: courses_2) {
			course.print_course();
		}
		ArrayList<Course> courses_3 = Database.get_course("CSCI", "104");
		for(Course course: courses_3) {
			course.print_course();
		}
		ArrayList<Course> courses_4 = Database.get_course("CSCI", "270");
		for(Course course: courses_4) {
			course.print_course();
		}
		courses.add(courses_3.get(0));
		courses.add(courses_4.get(0));
		courses.add(courses_2.get(1));
		Schedule schedule = new Schedule(courses, 2);
		System.out.println(schedule.is_valid());*/
	}
}
