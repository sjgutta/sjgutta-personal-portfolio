package final_project;

import java.util.ArrayList;
import java.util.Calendar;

public class Schedule {
	
	public int schedule_id;
	public ArrayList<Course> courses;
	public int user_id;
	
	
	Schedule(ArrayList<Course> courses, int user_id){
		this.courses = courses;
		this.user_id = user_id;
	}
	
	public void add_schedule_id(String id) {
		schedule_id = Integer.valueOf(id);
	}
	
	public boolean add_course(Course new_course) {
		this.courses.add(new_course);
		if(this.is_valid()) {
			return true;
		}else {
			this.courses.remove(this.courses.size()-1);
			return false;
		}
	}
	
	//remove last course, used in generation algorithm
	public void remove_last_course() {
		this.courses.remove(this.courses.size()-1);
	}
	
	//method to print schedule
	public void print_schedule() {
		System.out.println("YOUR SCHEDULE");
		for(Course course: this.courses) {
			course.print_course();
		}
	}
	
	//method to check if the schedule is valid
	public boolean is_valid() {
		//create 2d array to represent a schedule and initialize to 0 for each time slot
		int[][] schedule_slots = new int[5][24];
		for(int i = 0; i < schedule_slots.length; i++){
		    for(int j = 0; j < schedule_slots[i].length; j++){
		       schedule_slots[i][j] = 0;
		    }
		}
		
		Calendar calendar = Calendar.getInstance();
		//slowly add courses, updating the array and seeing if each added courses is valid
		for(Course course:this.courses) {
			//System.out.println("Course is " + course.prefix + course.code);
			int[] days_list = course.get_days_list();
			//System.out.println("Days are " + days_list[0] + " and " + days_list[1]);
			calendar.setTime(course.start_time);
			int start_hour = calendar.get(Calendar.HOUR_OF_DAY);
			calendar.setTime(course.end_time);
			int end_hour = calendar.get(Calendar.HOUR_OF_DAY);
			int end_minutes = calendar.get(Calendar.MINUTE);
			if(end_minutes==0) {
				end_hour--;
			}
			
			//for each day for the course, verify the time slot isn't taken
			//if the slot is open, fill the time slot with this course
			for(int day: days_list) {
				for(int i=start_hour; i<=end_hour; i++) {
					if(schedule_slots[day][i]==1) {
						return false;
					}else {
						schedule_slots[day][i]=1;
					}
				}
			}
		}
		return true;
	}
}
