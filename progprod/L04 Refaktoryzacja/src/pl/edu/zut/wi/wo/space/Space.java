package pl.edu.zut.wi.wo.space;

public class Space {
	private Person defaultOwner;
	
	public Space(Person owner) {
		this.defaultOwner = owner;
	}

	public Person getDefaultOwner() {
		return defaultOwner;
	}

	public void setDefaultOwner(Person owner) {
		this.defaultOwner = owner;
	}
}
