package final_project;

public class StudyRoom {
	private int id;
	private String name;
	private String description;
	
	StudyRoom(int id, String name, String description){
		this.id = id;
		this.name = name;
		this.description = description;
	}
	
	public void get_reservations_list() {
		Database.get_room_reservations(this.id);
	}
}
