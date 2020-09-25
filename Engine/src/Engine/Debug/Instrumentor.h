#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>

namespace Engine
{
  struct ProfileResult
  {
    std::string _name;
    long long _start, _end;
    size_t _threadID;
  };

  struct InstrumentationSession
  {
    std::string _name;
  };

  class Instrumentor
  {
  public:
    Instrumentor()
      : m_CurrentSession(nullptr), m_ProfileCount(0) {}

    inline void BeginSession(const std::string& name, const std::string& path = "results.json")
    {
      m_OutputStream.open(path);
      WriteHeader();
      m_CurrentSession = new InstrumentationSession{ name };
    }

    inline void EndSession()
    {
      WriteFooter();
      m_OutputStream.close();
      delete m_CurrentSession;
      m_CurrentSession = nullptr;
      m_ProfileCount = 0;
    }

    inline void WriteHeader()
    {
      m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
      m_OutputStream.flush();
    }

    inline void WriteProfile(const ProfileResult& result)
    {
      if (m_ProfileCount++ > 0)
      {
        m_OutputStream << ",";
      }
      std::string name = result._name;
      std::replace(name.begin(), name.end(), '"', '\'');

      m_OutputStream << "{";
      m_OutputStream << "\"cat\":\"function\",";
      m_OutputStream << "\"dur\":" << (result._end - result._start) << ',';
      m_OutputStream << "\"name\":\"" << name << "\",";
      m_OutputStream << "\"ph\":\"X\",";
      m_OutputStream << "\"pid\":0,";
      m_OutputStream << "\"tid\":" << result._threadID << ",";
      m_OutputStream << "\"ts\":" << result._start;
      m_OutputStream << "}";

      m_OutputStream.flush();
    }

    inline void WriteFooter()
    {
      m_OutputStream << "]}";
      m_OutputStream.flush();
    }

    inline static Instrumentor& Get()
    {
      static Instrumentor instance;
      return instance;
    }
  private:
    InstrumentationSession* m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;
  };

  class InstrumentationTimer
  {
  public:
    InstrumentationTimer(const char* name)
      : m_Name(name), m_Stopped(false)
    {
      m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~InstrumentationTimer()
    {
      if (!m_Stopped)
      {
        Stop();
      }
    }

    inline void Stop()
    {
      auto endTimepoint = std::chrono::high_resolution_clock::now();

      long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
      long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

      size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
      Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

      m_Stopped = true;
    }

  private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
  };

#define EN_PROFILE 1
#if EN_PROFILE
  #define EN_PROFILE_BEGIN_SESSION(name, path) ::Engine::Instrumentor::Get().BeginSession(name, path)
  #define EN_PROFILE_END_SESSION() ::Engine::Instrumentor::Get().EndSession()
  #define EN_PROFILE_SCOPE(name) ::Engine::InstrumentationTimer timer##__LINE__(name)
  #define EN_PROFILE_FUNCTION() EN_PROFILE_SCOPE(__FUNCSIG__)
#else
  #define EN_PROFILE_BEGIN_SESSION(name, path)
  #define EN_PROFILE_END_SESSION()
  #define EN_PROFILE_SCOPE(name)
  #define EN_PROFILE_FUNCTION()
#endif
}