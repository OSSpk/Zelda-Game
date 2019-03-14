#pragma once

class Princess
{
private:
	bool is_Alive;
	bool along; //if princess is along with you

public:
	Princess();
	~Princess();

	bool	 getAlongState();
	void	 setAlongState(bool);
	bool	 getLivingState();
	void	 setLivingState(bool);
};