// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_POLLER_H
#define MUDUO_NET_POLLER_H

#include <map>
#include <vector>

#include "muduo/base/Timestamp.h"
#include "muduo/net/EventLoop.h"

namespace muduo
{
  namespace net
  {

    class Channel;

    ///
    /// Base class for IO Multiplexing
    ///
    /// This class doesn't own the Channel objects.
    class Poller : noncopyable
    {
    public:
      typedef std::vector<Channel *> ChannelList;

      Poller(EventLoop *loop);
      virtual ~Poller();

      /// Polls the I/O events.
      /// Must be called in the loop thread.
      /**
       * 获得当前活动的IO事件，然后填充到调用方传入的activeChannels
       * 返回epoll_wait/poll函数return的时刻（Timestamp对象）
       */
      virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;

      /// Changes the interested I/O events.
      /// Must be called in the loop thread.
      virtual void updateChannel(Channel *channel) = 0;

      /// Remove the channel, when it destructs.
      /// Must be called in the loop thread.
      virtual void removeChannel(Channel *channel) = 0;
      // 判断当前Poller对象是否持有指定通道
      virtual bool hasChannel(Channel *channel) const;

      static Poller *newDefaultPoller(EventLoop *loop);

      void assertInLoopThread() const
      {
        ownerLoop_->assertInLoopThread();
      }

    protected:
      // ChannelMap ：fd 到 Channel *的映射
      typedef std::map<int, Channel *> ChannelMap;
      ChannelMap channels_;

    private:
      EventLoop *ownerLoop_;
    };

  } // namespace net
} // namespace muduo

#endif // MUDUO_NET_POLLER_H
