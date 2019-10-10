
int	init_des_context(t_des_context *des, t_cipher_context *c)
{
	if (!(des = malloc(sizeof(*des))))
		return (0);
	if (!(des->out = ft_dstr_init()))
		return (0);
	des->key[0] = ft_ssl_des_pbkdf(c->key[0]);
	return (0);
}
