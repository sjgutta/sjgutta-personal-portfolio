package final_project;

import java.util.ArrayList;

public class ScheduleGenerator {
	
	public static Schedule generateSchedule(String first_prefix, String first_code, String second_prefix, String second_code,
			String third_prefix, String third_code, String fourth_prefix, String fourth_code, String pref) {
		
		ArrayList<Course> schedule_courses = new ArrayList<Course>();
		Schedule result = new Schedule(schedule_courses, 1);
		
		//creating the course pools to be built
		ArrayList<ArrayList<Course>> course_pools = new ArrayList<ArrayList<Course>>();
		
		//create list of sections for each desired course
		ArrayList<Course> first_course = Database.get_course(first_prefix, first_code);
		ArrayList<Course> second_course = Database.get_course(second_prefix, second_code);
		System.out.println(second_course.size());
		ArrayList<Course> third_course = Database.get_course(third_prefix, third_code);
		ArrayList<Course> fourth_course = Database.get_course(fourth_prefix, fourth_code);
		
		//separate each course into a separate list of sections for each section type, add to course_pool
		if(first_course.size()!=0) {
			ArrayList<String> course_one_types = ScheduleGenerator.SectionTypes(first_course);
			if(course_one_types.size()==1) {
				course_pools.add(first_course);
			}else {
				for(int i=0; i<course_one_types.size(); i++) {
					String this_type = course_one_types.get(i);
					ArrayList<Course> this_type_sections = new ArrayList<Course>();
					for(int j=0; j<first_course.size(); j++) {
						if(first_course.get(j).course_type.equals(this_type)) {
							this_type_sections.add(first_course.get(j));
						}
					}
					course_pools.add(this_type_sections);
				}
			}
		}
		if(second_course.size()!=0) {
			ArrayList<String> course_two_types = ScheduleGenerator.SectionTypes(second_course);
			if(course_two_types.size()==1) {
				course_pools.add(second_course);
			}else {
				for(int i=0; i<course_two_types.size(); i++) {
					String this_type = course_two_types.get(i);
					ArrayList<Course> this_type_sections = new ArrayList<Course>();
					for(int j=0; j<second_course.size(); j++) {
						if(second_course.get(j).course_type.equals(this_type)) {
							this_type_sections.add(second_course.get(j));
						}
					}
					course_pools.add(this_type_sections);
				}
			}
		}
		if(third_course.size()!=0) {
			ArrayList<String> course_three_types = ScheduleGenerator.SectionTypes(third_course);
			if(course_three_types.size()==1) {
				course_pools.add(third_course);
			}else {
				for(int i=0; i<course_three_types.size(); i++) {
					String this_type = course_three_types.get(i);
					ArrayList<Course> this_type_sections = new ArrayList<Course>();
					for(int j=0; j<third_course.size(); j++) {
						if(third_course.get(j).course_type.equals(this_type)) {
							this_type_sections.add(third_course.get(j));
						}
					}
					course_pools.add(this_type_sections);
				}
			}
		}
		if(fourth_course.size()!=0) {
			ArrayList<String> course_four_types = ScheduleGenerator.SectionTypes(fourth_course);
			if(course_four_types.size()==1) {
				course_pools.add(fourth_course);
			}else {
				for(int i=0; i<course_four_types.size(); i++) {
					String this_type = course_four_types.get(i);
					ArrayList<Course> this_type_sections = new ArrayList<Course>();
					for(int j=0; j<fourth_course.size(); j++) {
						if(fourth_course.get(j).course_type.equals(this_type)) {
							this_type_sections.add(fourth_course.get(j));
						}
					}
					course_pools.add(this_type_sections);
				}
			}
		}
		
		//sort each course pool based on the user preference
		if(pref.equals("early")) {
			for(int i=0; i<course_pools.size(); i++) {
				ScheduleGenerator.sortEarly(course_pools.get(i));
			}
		}else if(pref.equals("later")) {
			for(int i=0; i<course_pools.size(); i++) {
				ScheduleGenerator.sortLater(course_pools.get(i));
			}
		}else {
			for(int i=0; i<course_pools.size(); i++) {
				ScheduleGenerator.sortMidDay(course_pools.get(i));
			}
		}
		
		
		/*for(int i=0; i<course_pools.size(); i++) {
			System.out.println("Next Course Pool");
			System.out.println("**************************");
			for(Course course: course_pools.get(i)) {
				course.print_course();
			}
		}*/
		
		boolean success = ScheduleGenerator.recursiveGenerator(course_pools, result, 0);
		System.out.println(success);
		
		//System.out.println("Printing schedule");
		//result.print_schedule();
		return result;
	}
	
	public static boolean recursiveGenerator(ArrayList<ArrayList<Course>> course_pools, Schedule result, int current_pool) {
		ArrayList<Course> this_pool = course_pools.get(current_pool);
		for(int i=0; i<this_pool.size(); i++) {
			if(result.add_course(this_pool.get(i))) {
				if(current_pool == course_pools.size()-1) {
					return true;
				}else {
					if(ScheduleGenerator.recursiveGenerator(course_pools, result, current_pool + 1)) {
						return true;
					}else {
						result.remove_last_course();
					}
				}
			}
		}
		return false;
	}
	
	public static void sortEarly(ArrayList<Course> course_list) {
		for(int i=1; i<course_list.size(); i++) {
			Course current = course_list.get(i);
	        int j = i - 1;
	        while(j >= 0 && current.end_time.compareTo(course_list.get(j).end_time) != 1) {
	            course_list.set(j+1, course_list.get(j));
	            j--;
	        }
	        // at this point we've exited, so j is either -1
	        // or it's at the first element where current >= a[j]
	        course_list.set(j+1, current);
		}
	}
	
	public static void sortLater(ArrayList<Course> course_list) {
		for(int i=1; i<course_list.size(); i++) {
			Course current = course_list.get(i);
	        int j = i - 1;
	        while(j >= 0 && current.start_time.compareTo(course_list.get(j).start_time) >= 1) {
	            course_list.set(j+1, course_list.get(j));
	            j--;
	        }
	        // at this point we've exited, so j is either -1
	        // or it's at the first element where current >= a[j]
	        course_list.set(j+1, current);
		}
	}
	
	public static void sortMidDay(ArrayList<Course> course_list) {
		for(int i=1; i<course_list.size(); i++) {
			Course current = course_list.get(i);
	        int j = i - 1;
	        while(j >= 0 && current.distanceFromNoon() < course_list.get(j).distanceFromNoon()) {
	            course_list.set(j+1, course_list.get(j));
	            j--;
	        }
	        // at this point we've exited, so j is either -1
	        // or it's at the first element where current >= a[j]
	        course_list.set(j+1, current);
		}
	}
	
	public static ArrayList<String> SectionTypes(ArrayList<Course> courses) {
		ArrayList<String> course_types = new ArrayList<String>();
		for(int i=0; i<courses.size(); i++) {
			String type = courses.get(i).course_type;
			if(!course_types.contains(type)) {
				course_types.add(type);
			}
		}
		return course_types;
	}
	
	public static void main(String[] args) {
		//ArrayList<Course> courses = Database.get_course("CSCI", "201");
		//Schedule result = ScheduleGenerator.generateSchedule("CSCI", "201", "CSCI", "170", "BUAD", "304", "", "", "later");
		//result.print_schedule();
		ArrayList<Schedule> results = Database.get_user_schedules(2);
		results.get(1).print_schedule();
	}
}
