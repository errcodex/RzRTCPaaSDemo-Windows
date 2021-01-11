//
// Created by yhy on 11/1/20.
//

#ifndef PAASSDK_INTERACTIVEMANAGE_H
#define PAASSDK_INTERACTIVEMANAGE_H

#include <map>
#include <list>
#include <mutex>
#include <atomic>
#include <thread>
#include <functional>
#include <condition_variable>

#include "RZTime.h"
#include "RZLog.h"

namespace rz{

    struct InteractiveTask{
        std::string taskName;
        uint32_t startTime;
        std::function<void ()> taskFun = nullptr;
        std::function<void()> taskOverFun = nullptr;
        explicit InteractiveTask(std::string name,std::function<void ()> fun){
            taskName = name;
            taskFun = fun;
            startTime = RZTime::opts();
        }
    };

    class AsyncQuit;

    class InteractiveManage{
    private:
        struct timedTask {
            std::function<void(void)> taskFun = nullptr;              //������
            int timeInterval = 0;                                     //������ü��   ms     ��С��� 10ms
            int taskImplemenCount = 0;                                //�����Ѿ�ִ�еĴ���
            uint32_t taskStartTime = 0;                                    //��������ʱ��
        };

        static std::mutex timedTaskPoolMX;
        static std::map<std::string, std::shared_ptr<timedTask>> timedTaskPool;    //��ʱ�����

        static std::mutex taskPoolMX;
        static std::list<InteractiveTask> taskPool;
        static std::thread workTh;

        static std::condition_variable conditionVariable;

        static std::atomic<bool> running;

        //����̬������ѭ���������ͷ�׼�� �첽�˳������ھ�̬����asyncQuit���������������˳��߳�
        //TODO ��˽���̬����asyncQuit���������߳�InteractiveManage::workTh�ĺ� ���ɸ���
        static AsyncQuit asyncQuit;

    protected:
        static void workFun();
    public:

        static void addTask(InteractiveTask task);

        /**
         * ע�ᶨʱ����
         * @param taskId ����ID
         * @param taskFun ����ִ�к���
         * @param timeInterval ����ִ�м�� /ms ����С��10ms ϵͳ������������ʱ�䡢��ǰʱ�������ִ�м������ִ�д���,���Ա��ϳ�ʱ���ڵ�����ִ�д�������������һ����
         * @param Immediate �Ƿ�����ִ��
         */
        static void registTimedTask(const std::string& taskId, std::function<void(void)> taskFun, int timeInterval, bool Immediate);

        /**
         * �Ƴ���ʱ����
         * @param taskId ����ID
         */
        static void removeTimedTask(const std::string& taskId);

        static std::thread::id getThreadId();

        static void taskClear();

        static void start();

        static void stop();
    };

    class AsyncQuit {
    public:
        
        ~AsyncQuit(){
            InteractiveManage::stop();
        }
    };
}


#endif //PAASSDK_INTERACTIVEMANAGE_H
