#include <ykm/async_machine.hpp>

#include <iostream>

bool bExit = false;

class test_task : public ykm::async_pip_wrap<test_task>
{
  public:
    async_handle start()
    {
        std::cout << "test task start" << std::endl;

        return async_next(&test_task::m_wait);
    };

    async_handle m_wait()
    {
        if (i == 0)
        {
            ++i;
            std::cout << "test task 1s" << std::endl;
            return async_wait(1000, &test_task::m_wait);
        }
        else if (i == 1)
        {
            ++i;
            std::cout << "test task 2s" << std::endl;
            return async_wait(2.0f, &test_task::m_wait);
        }
        else
        {
            bExit = true;
            return async_final(&test_task::m_wait);
        }
    };

  private:
    int i = 0;
};

int main()
{
    ykm::async_machine am;
    am.add_task(&test_task::start);

    while (!bExit) { am.process_next(); }

    return 0;
}
