/*
 *  Copyright (c) 2016, https://github.com/zhatalk
 *  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NUBULA_NET_HANDLER_MTPROTO_MTPROTO_HANDLER_H_
#define NUBULA_NET_HANDLER_MTPROTO_MTPROTO_HANDLER_H_

#include "nebula/net/handler/nebula_base_handler.h"
#include "nebula/net/handler/nebula_event_callback.h"

using MTProtoEventCallback = NebulaEventCallback<nebula::MTProtoPipeline, std::unique_ptr<folly::IOBuf>>;

class MTProtoHandler :
    public wangle::HandlerAdapter<std::unique_ptr<folly::IOBuf>, std::unique_ptr<folly::IOBuf>>,
    public nebula::NebulaBaseHandler {
public:
  explicit MTProtoHandler(nebula::ServiceBase* service)
    : NebulaBaseHandler(service) {}
  
  //////////////////////////////////////////////////////////////////////////
  // 重载 HandlerAdapter<std::unique_ptr<IOBuf>>
  void read(Context* ctx, std::unique_ptr<folly::IOBuf> msg) override;
  // folly::Future<folly::Unit> write(Context* ctx, std::unique_ptr<folly::IOBuf> out) override;
  
  void readEOF(Context* ctx) override;
  void readException(Context* ctx, folly::exception_wrapper e) override;
  
  void transportActive(Context* ctx) override;
  void transportInactive(Context* ctx) override;

  folly::Future<folly::Unit> close(Context* ctx) override;
  
private:
  // TODO(@benqi): s2s应用场景里，连接发起方需要保活，逻辑基本一样，
  //  后续zrpc_client_handler/zproto_handler等统一处理
  // static void DoHeartBeat(uint64_t conn_id, uint32_t timeout);
};

void ModuleMTProtoInitialize();

#endif
