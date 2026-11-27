import test from 'node:test';
import assert from 'node:assert/strict';
import { registerDemoTools } from '../lib/webmcp.mjs';
import { initialState, reducer } from '../lib/demo-model.mjs';
test('optional tool contracts use the same state, validate atomically, and unregister', () => {
  let state = initialState();
  const tools = new Map();
  let signal;
  const cleanup = registerDemoTools(
    {
      registerTool(tool, options) {
        tools.set(tool.name, tool);
        signal = options.signal;
      },
    },
    () => state,
    (values) => {
      for (const [key, value] of Object.entries(values))
        state = reducer(state, { type: 'PARAM', key, value });
    },
  );
  const read = tools.get('read_laser_demo_state'),
    configure = tools.get('configure_laser_demo_parameters');
  assert.equal(read.annotations.readOnlyHint, true);
  assert.equal(configure.inputSchema.additionalProperties, false);
  assert.deepEqual(configure.execute({ power: 45, mode: 'CW' }).parameters, {
    power: 45,
    mode: 'CW',
    on: 600,
    off: 700,
    aim: 100,
  });
  assert.throws(() => configure.execute({ power: 55, on: 11 }));
  assert.equal(state.params.power, 45);
  assert.equal(read.execute().screen, 'main');
  cleanup();
  assert.equal(signal.aborted, true);
});
test('unsupported browser works without the optional integration', () =>
  assert.doesNotThrow(() =>
    registerDemoTools(
      undefined,
      () => {},
      () => {},
    )(),
  ));
