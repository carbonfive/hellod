-module(hello_server).
-behaviour(gen_server).

%% API
-export([start_link/0]).

%% gen_server callbacks
-export([
          init/1, 
          handle_call/3, handle_cast/2, 
          handle_info/2,
   terminate/2, code_change/3]).

-record(state, {}).
-define(SERVER, ?MODULE). 
-define(PORT, 8084).


start_link() ->
    gen_server:start_link({local, ?SERVER}, ?MODULE, [], []).

init([]) ->
    misultin:start_link([
       {port, ?PORT}, {loop, fun(Req) -> handle_http(Req, ?PORT) end}
      ]),
    {ok, #state{}}.

terminate(_Reason, _State) ->
    misultin:stop(),
    ok.

code_change(_OldVsn, State, _Extra) ->
    {ok, State}.

handle_info(_Info, State) ->
    {noreply, State}.

handle_call(_Request, _From, State) ->
    {noreply, State}.

handle_cast(_Request, State) ->
    {noreply, State}.

% callback on request received
handle_http(Req, Port) ->  
  Req:ok([{"Content-Type", "text/html"}],
  ["<html><body><h1>Hello World</h1></body></html>\r\n"]).
