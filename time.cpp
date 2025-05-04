class TIME {
	public:
		void init(void)
		{
			seconds = 0;
			useconds = 0;
			clock0 = clock();
			clock1 = clock();
			diffclock = 0L;
		}
		void update(void)
		{
			clock1 = clock();
			diffclock = (u6) clock1 - (u6) clock0;
			useconds += diffclock;
			seconds += (useconds / 1000000);
			useconds = useconds % 1000000;
			clock0 = clock();
		}
		double dclock(void)
		{
			return (double) seconds + (double) useconds / 1000000.0;
		}
	private:
		u6 seconds;
		u6 useconds;
		clock_t clock0;
		clock_t clock1;
		u6 diffclock;
};

