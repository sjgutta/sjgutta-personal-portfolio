package final_project;

import java.sql.Time;
import java.util.List;

import com.jaunt.Element;
import com.jaunt.Elements;
import com.jaunt.Node;
import com.jaunt.NotFound;
import com.jaunt.ResponseException;
import com.jaunt.UserAgent;

public class Scraper {
	public static void scrapeClasses() {
		UserAgent ua = new UserAgent();
		try {
			ua.visit("https://classes.usc.edu/term-20203/");
		} catch (ResponseException e) {
			// TODO Auto-generated catch block
			System.out.println("Error");
		}

		Elements links = ua.doc.findEvery("<ul class=sortable>").findEvery("<a>");
		boolean reached_cinematic = false;
		//Looking for every School
		for (Element link : links) {
			try {
				if(link.getAt("href").equals("https://classes.usc.edu/term-20203/classes/cnma/")) {
					reached_cinematic = true;
				}
			} catch (NotFound e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			if(reached_cinematic) {
				try {
					System.out.println(link.getAt("href"));
					//Visiting every Department ex. ALI, AMST, ANTH
					ua.visit(link.getAt("href"));
					
					//Getting the div that contains every class from the same department ex. ALI224, ALI225.
					Element insideLink = ua.doc.findFirst("<div class=course-table>");
					
					//Create the ArrayList to later send to a method that stores to our database
					
					
					//Getting every class as a separate node
					List<Node> childNodes = insideLink.getChildNodes();
					
					//Going throught every node and scraping the data that we need
					for (Node node : childNodes) { 
						if (node.getType() == Node.ELEMENT_TYPE) {
	
							if (!((Element) node).getName().equals("p")) {
								try {
									List<Node> innernodes = ((Element) node).getChildNodes();
	
									Node firstDiv = innernodes.get(0);
									Node secondDiv = innernodes.get(1);
	
									Element prefixNCode = ((Element) firstDiv).findFirst("<strong>");
	
									List<Element> tableOfCourses = ((Element) secondDiv).findFirst("<table>")
											.getChildElements();
	
									Element instructor = null;
									Element classroom = null;
									Element days = null;
									Element time = null;
									Element type = null;
									
									for (int j = 1; j < tableOfCourses.size(); ++j) {
										Element tr = tableOfCourses.get(j);
										instructor = tr.findFirst("<td class=instructor>");
										classroom = tr.findFirst("<td class=\"location\"");
										days = tr.findFirst("<td class=days>");
										time = tr.findFirst("<td class=time>");
										type = tr.findFirst("<td class=type>");
										String prefix = "";
										String code = "";
										String instructorStr = instructor.getTextContent();
										String classroomStr = "";
										String[] str = prefixNCode.innerHTML().toString().split(" ");
										String daysStr = "";
										String startTimeStr = "";
										String endTimeStr = "";
										String typeStr = "";
	
										// Setting class prefix and code
										if (str.length == 2) {
											prefix = str[0];
											code = str[1];
											code = code.substring(0, code.length() - 1);
										} else {
											System.out.println("There are classes with different prefix and code format "
													+ prefixNCode.innerHTML());
										}
	
										// Setting classroom
										classroomStr += classroom.getTextContent();
	
										// Setting days
										daysStr = days.innerHTML().toString();
										str = time.innerHTML().toString().split("-");
	
										// Setting hours
										if (str.length == 2) {
											startTimeStr = str[0];
											endTimeStr = str[1];
											// Setting class type
											typeStr = type.innerHTML().toString();
											
											String combined_time_string = startTimeStr + ":" + endTimeStr;
											Time startTime = Database.parse_time_string_start(combined_time_string);
											Time endTime = Database.parse_time_string_end(combined_time_string);
											daysStr = Database.parse_days_string(daysStr);
											System.out.println(prefix + " " + code + " " + "Instructor: " + instructorStr + " "
													+ "Days: " + daysStr + " " + startTime + "-" + endTime + " "
													+ classroomStr + " " + typeStr);
											Database.insert_course(prefix, code, instructorStr, classroomStr, daysStr, startTime, endTime, typeStr);
										} else {
											if (time.innerHTML().toString().equals("TBA")) {
												startTimeStr = "TBA";
												endTimeStr = "";
											} else
												System.out.println("There are classes with different time format: "
														+ time.innerHTML().toString());
										}
										
										
										//Save to an ArrayList 
									}
								} catch (NotFound e) {
									//System.out.println("Error printinng getting the link");
								}

							}
	
						}
	
					}
					
					//Call the function to save to our data base
					
					
	
				} catch (NotFound | ResponseException e) {
	
					System.out.println("Error outside");
				}
			}
		}
	}
	
	public static void main(String[] args) {
		Scraper.scrapeClasses();
	}
}