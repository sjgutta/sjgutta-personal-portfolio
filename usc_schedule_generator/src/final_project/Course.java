package final_project;

import java.sql.Time;
import java.util.ArrayList;

public class Course {
	//items corresponding to database fields
	public String prefix;
	public String code;
	public String professor_name;
	public String classroom;
	public String days;
	public Time start_time;
	public Time end_time;
	public String course_type;
	
	//constructor
	Course(String prefix, String code, String professor_name, String classroom, 
			String days, Time start_time, Time end_time, String course_type){
		this.prefix = prefix;
		this.code = code;
		this.professor_name = professor_name;
		this.classroom = classroom;
		this.days = days;
		this.start_time = start_time;
		this.end_time = end_time;
		this.course_type = course_type;
	}
	
	public int[] get_days_list() {
		String[] parts = this.days.split(",");
		//System.out.println("parts are " + parts[0] + " and " + parts[1]);
		int[] result = new int[parts.length];
		//System.out.println("Result is length " + result.length);
		for(int i=0; i<parts.length; i++) {
			int this_day = 0;
			//choose proper index value to be used in schedule functions based on the day
			if(parts[i].equals("M")) {
				this_day=0;
			}else if(parts[i].equals("T")) {
				this_day=1;
			}else if(parts[i].equals("W")) {
				this_day=2;
			}else if(parts[i].equals("TH")) {
				this_day=3;
			}else if(parts[i].equals("F")) {
				this_day=4;
			}
			//System.out.println("This day is " + this_day);
			result[i] = this_day;
		}
		return result;
		
	}
	
	public long distanceFromNoon() {
		Time noon = Time.valueOf("12:00:00");
		long start_diff = Math.abs(this.start_time.getTime() - noon.getTime())/60000;
		long end_diff = Math.abs(this.end_time.getTime() - noon.getTime())/60000;
		if(start_diff < end_diff) {
			return start_diff;
		}else {
			return end_diff;
		}
	}
	
	//This function is useful for testing that right courses are being retrieved
	public void print_course() {
		System.out.println("Course: " + this.prefix + this.code);
		System.out.println("Professor: " + this.professor_name);
		System.out.println("Located in: " + this.classroom + " on " + this.days);
		System.out.println("Starts at: " + this.start_time + " and ends at " + this.end_time);
		System.out.println("This course is a " + this.course_type + " type of section");
		System.out.println("-----------------------------------------------------------");
	}
	
}
