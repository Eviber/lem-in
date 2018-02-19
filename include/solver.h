
#ifndef SOLVER_H
# define SOLVER_H

int		save_info(int set, int new_depth, t_room *o_room, t_env *env);
void	lock_path(t_env *env);
void	reset_room(t_env *env);

#endif
