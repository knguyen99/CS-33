long cread_alt(long *xp){
	long good = xp[-1];
	long bad = -1;
	if (!xp) good = bad;
	return good;
}
