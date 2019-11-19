char	*nrandom(size_t n)
{
	char	*ret;
	int		fd;

	if (!(fd = open("/dev/urandom", O_RDONLY)))
		return (NULL);
	if (!(ret = malloc(sizeof(*ret) * (n + 1))))
		return (NULL);
	if (ft_ssl_read(fd, ret, n) > 0)
		return (ret);
	free(ret);
	return (NULL);
}
