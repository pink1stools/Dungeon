// ---------------------------------------------------------------------
 
// ---------------------------------------------------------------------


//#define STATUS_WIN  			0
#define STATUS_GAME_OVER		1
#define STATUS_ATT  			2
#define STATUS_DEF		        10
#define STATUS_END          	4
#define STATUS_WIN		5
#define STATUS_START			3

class c_dungeon 
{
public:

	c_dungeon();
	int			start();

    int		nSelectedPKG;
	int		nPKGListTop;
	int		nTotalPKG;
	bool	bDeleting;	
	int		nPKGID;

	int		nStatus;
	
//	c_pkglist	*pkglst;


	void		startgame();
    void		wait(int seconds);
	void		makedun();
	void		shop();
	void		drawmap();
	void		combat();
	void		getcoord();
	void		normal();
	void		Frame();
	void		DisplayFrame();
	void		InputFrame();
	void		DlgDisplayFrame();
	
	
	//void        shutdown_system(u8 mode);

private:
	// ...
};

extern c_dungeon* dungeon;
