package final_project;

import java.sql.Date;
import java.sql.Time;

public class Reservation {
	public int user;
	public int room;
	public Time start_time;
	public Time end_time;
	public Date reservation_date;
	
	Reservation(int user, int room, Time start_time, Time end_time, Date reservation_date){
		this.user = user;
		this.room = room;
		this.start_time = start_time;
		this.end_time = end_time;
		this.reservation_date = reservation_date;
	}
	
	public void save_reservation() {
		Database.insert_reservation(this);
	}
}
