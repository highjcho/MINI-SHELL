#include "../../includes/redirect.h"

	/*
	in_out fd cmd 구조체에 저장
	각 in_out에 기록할 수 있도록 오픈 - 한 PL에 아웃파일이 있으면 파이프에 써지는 게 없어서 파이프라인 명령어 라인에 입력이 영향을 받지 않음
	*/

int redirect_files(t_ast *ast, t_cmd *cmd)
{
	if (here_doc == true) // ast << here_doc 있을 경우
	{
		/*
		fork
		자식 : fd[1]에 gnl로 delimiter까지 입력 받기 fd[0] 닫기
		부모 : in_fd = fd[0]; 으로 만들어주기, fd[1] 닫기
		*/
	}
	else if (rdr_in == true) // ast 돌면서 < infile 있을 경우
	{
		if (cmd->in_fd != -1) // infile을 연적이 없거나 || 파이프를 사용한 적이 없을 경우 (? 확실하지 않음)
			close(cmd->in_fd); // 직전 파이프 fd[0]이 열려 있으니 닫고, 또 이전 노드에서 다른 infile이 열렸을 수도 있으니까 또 닫음
		cmd->in_fd = open infile; // 리다이렉션에 맞게 열기
	}
	else if (rdr_out == true) // outfile 있으면 outfile >, >> 에 따라 다르게 열어주기
	{
		if (cmd->out_fd != -1 && cmd->out_fd == 1) // 표준입력이 들어왔을 때 닫으면 안되니까,,? <- 이건 생각 필요
			close(cmd->out_fd); // 여러개의 아웃이 들어왔을 때 직전 아웃파일 닫기, bash는 아웃파일 여러개 들어오면 마지막 거에만 함
		cmd->out_fd = open outfile;
	} // 여기까지는 fork 안해도 똑같
}
