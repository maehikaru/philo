/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeharahikaru <maeharahikaru@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:38:37 by maeharahika       #+#    #+#             */
/*   Updated: 2023/11/27 04:11:41 by maeharahika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>

# define CONTINUE 0
# define DEATH 1
# define FINISHED 2

typedef struct s_philo
{
	pthread_t			tid; //スレッドID
	int					idx; //フィロソファーの番号
	int					last_eat; //最後に食べた時刻
	int					n_ate; //食事した回数
	struct s_table		*tbl; //フィロソファーが所属するテーブルを指すポインタ
	pthread_mutex_t		*fork_l; //フィロソファーの左側のフォークを指すポインタ
	pthread_mutex_t		*fork_r; //フィロソファーの右側のフォークを指すポインタ
}	t_philo;

typedef struct s_table
{
	int				n_philos; //フィロソファーの数
	int				time_die; //死亡判定時間
	int				time_eat; //食事時間
	int				time_slp; //睡眠時間
	int				max_eat; //食事回数
	long long		start_ms; //プログラム開始時刻
	pthread_mutex_t	stop_lock; //フィロソファーの停止を制御するためのミューテックス
	int				to_stop; //フィロソファーの停止フラグを表す整数値
	pthread_mutex_t	waiter; //フィロソファーの待機を制御するためのミューテックス
	pthread_mutex_t	*forks; //フィロソファーが使用するフォークの配列へのポインタ
	t_philo			*philos; //フィロソファーの情報を格納する t_philo 構造体の配列へのポインタ
}	t_table;

int			ft_atoi(const char *str);
long		ft_strtol(const char *str, int base_num);
void		*ft_calloc(size_t count, size_t size);
int			init_handler(t_table *tbl, int argc, char **argv);
void		thread_handler(t_table *tbl);
long long	get_cur_ms(void);
void		thread_monitor(t_table *tbl);
void		final_handler(t_table *tbl);
void		ft_xprintf(int idx, char *str, t_table *tbl);
void		ft_xusleep(int microsec);
int			ft_xatoi(const char *str, bool *to_exit);

#endif
// INT＝43億ミリセカンド＝4294967秒＝1193時間