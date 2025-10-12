/*
** ���\�[�X�T�[�o
*/

#include "DxLib.h"
#include "ResourceServer.h"

// �ÓI�����o����
std::unordered_map<std::string, int>	ResourceServer::_mapGraph;
std::unordered_map<std::string, ResourceServer::DIVGRAPH>	ResourceServer::_mapDivGraph;
std::unordered_map<std::string, int>	ResourceServer::_mapSound;


void    ResourceServer::Init()
{
	_mapGraph.clear();
    _mapDivGraph.clear();
    _mapSound.clear();
}

void    ResourceServer::Release()
{
    ClearGraph();
}

void	ResourceServer::ClearGraph()
{
    // ���ׂẴf�[�^�̍폜������
    for (auto itr = _mapGraph.begin(); itr != _mapGraph.end(); itr++)
    {
        DeleteGraph(itr->second);
    }
    _mapGraph.clear();

    for (auto itr = _mapDivGraph.begin(); itr != _mapDivGraph.end(); itr++)
    {
        for (int i = 0; i < itr->second.AllNum; i++) {
            DeleteGraph(itr->second.handle[i]);
        }
        delete[] itr->second.handle;
    }
    _mapDivGraph.clear();

    for (auto itr = _mapSound.begin(); itr != _mapSound.end(); itr++)
    {
        DeleteSoundMem(itr->second);
    }
    _mapSound.clear();

}


int		ResourceServer::LoadGraph(const TCHAR* FileName)
{
    // �L�[�̌���
    auto itr = _mapGraph.find(FileName);
    if (itr != _mapGraph.end())
    {
        // �L�[��������
        return itr->second;
    }
    // �L�[����������
    int cg = ::LoadGraph(FileName);     // DXLIB��API���ĂԂ̂ŁA::��擪�ɕt���A���̃N���X�̓������O�̊֐��Ƌ�ʂ���
    // �L�[�ƃf�[�^��map�ɓo�^
    _mapGraph[FileName] = cg;

    return cg;
}

int		ResourceServer::LoadDivGraph(const TCHAR* FileName, int AllNum,
    int XNum, int YNum,
    int XSize, int YSize, int* HandleBuf)
{
    // �L�[�̌���
    auto itr = _mapDivGraph.find(FileName);
    if (itr != _mapDivGraph.end())
    {
        // �L�[��������
        // �f�[�^���R�s�[
        for (int i = 0; i < itr->second.AllNum; i++) {
            HandleBuf[i] = itr->second.handle[i];
        }
        return 0;
    }
    // �L�[����������
    // �܂��̓��������쐬����
    int* hbuf = new int[AllNum];
    int err = ::LoadDivGraph(FileName,AllNum,XNum,YNum,XSize,YSize, hbuf);     // DXLIB��API���ĂԂ̂ŁA::��擪�ɕt���A���̃N���X�̓������O�̊֐��Ƌ�ʂ���
    if (err == 0) {
        // ����
        // �L�[�ƃf�[�^��map�ɓo�^
        _mapDivGraph[FileName].AllNum = AllNum;
        _mapDivGraph[FileName].handle = hbuf;
        // �f�[�^���R�s�[
        for (int i = 0; i < AllNum; i++) {
            HandleBuf[i] = hbuf[i];
        }
    }

    return err;

}


int		ResourceServer::LoadSoundMem(const TCHAR* FileName) {
    // �L�[�̌���
    auto itr = _mapSound.find(FileName);
    if (itr != _mapSound.end())
    {
        // �L�[��������
        return itr->second;
    }
    // �L�[����������
    int snd = ::LoadSoundMem(FileName);     // DXLIB��API���ĂԂ̂ŁA::��擪�ɕt���A���̃N���X�̓������O�̊֐��Ƌ�ʂ���
    // �L�[�ƃf�[�^��map�ɓo�^
    _mapSound[FileName] = snd;

    return snd;
}

