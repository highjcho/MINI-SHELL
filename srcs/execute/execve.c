#include "../../includes/execute.h"

static int	has_path(t_cmd *cmd, char **envp)
{
	cmd->path = ft_strdup(cmd->cmd[0]);
	if (!cmd->path)
		return (FALSE); // free.. 뭐뭐 해야하남..
	execve(cmd->path, cmd->cmd, envp);
	free(cmd->path); // 실패 시 이쪽으로 넘어 옴. 뭐뭐,, 프리해야하지..?
	// err code 127, minishell: cmd->cmd : command not found 띄우기
	return (FALSE);
}

static int need_to_make_path(t_env *env, t_cmd *cmd, char **envp)
{
	char	*tmp;
	int		i;

	i = -1;
	while (env->path[++i]) // 경로 탐색 끝날 때까지
	{
		tmp = ft_strjoin("/", cmd->cmd[0]);
		if (!tmp)
			return (FALSE);
		cmd->path = ft_strjoin(env->path[i], tmp);
		if (!cmd->path)
			return (FALSE);
		free(tmp);
		check = execve(cmd->path, cmd->cmd, envp); // 성공하면 걍 빠져나가야 하는 거 아닌지..?
		free(cmd->path); // cmd_path 만들어 둔거 프리하고 해야 됨 계속 실행
	}
	//free(cmd->path); // path 끝까지 돌았는데 맞는 cmd를 못찾았을 때
	// double_free(cmd->cmd); //에러처리 커맨드 없움. 종료코드 127
	printf("check: %d\n", check);
	return (FALSE);
}

int	execute_non_builtin(t_env *env, t_ast *ast, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	if (cmd->out_fd == 0) // outfile 없으면 out_fd에 파이프 쓰기 꽂아주기
		cmd->out_fd = fd[1]; 
	pid = fork();
	if (pid < 0)
		return (FALSE); // fork 오류
	if (pid == 0) // 자식 프로세스 25줄 넘으면 자식프로세스 따로 빼기
	{
		close(fd[0]); // 파이프 읽기 닫기
		dup_fd(cmd->in_fd, STDIN_FILENO); // infile || 직전 파이프 읽기로 표준입력 교체
		dup_fd(cmd->out_fd, STDOUT_FILENO); // outfile || 파이프 쓰기로 표준출력 교체
		if (cmd->cmd[0][0] == '/')
			check = has_path(cmd, envp);
		else
			check = need_to_make_path(env, cmd, envp);
		// if (check == FALSE)
			// 에러 핸들러 뭐 프리할 거 프리하고
	}
	close(fd[1]); // 파이프 쓰기 닫기 // 자식 실패하면 뭐 쓰는 거 없겠지????
	wait(&status);
	//waitpid(pid, &status, WNOHANG); // wnohang 왜 했었지?
	return (fd[0]); // infile 초기화 하고 다음 루틴에서 점검해서 있으면 인파일 dup, 없으면 read_fd dup
}