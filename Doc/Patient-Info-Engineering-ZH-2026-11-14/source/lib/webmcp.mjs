import { LIMITS } from './demo-model.mjs';
// Optional progressive enhancement. Ordinary browsers do not need WebMCP.
export function registerDemoTools(context, read, configure) {
  if (!context?.registerTool) return () => {};
  const lifecycle = new AbortController();
  const register = (tool) => {
    try {
      Promise.resolve(
        context.registerTool(tool, { signal: lifecycle.signal }),
      ).catch(() => {});
    } catch {
      /* Unsupported registries must not interrupt the demo. */
    }
  };
  register({
    name: 'read_laser_demo_state',
    description:
      'Read simulated laser UI parameters, current screen, and pending-record status. No hardware is connected.',
    inputSchema: {
      type: 'object',
      properties: {},
      additionalProperties: false,
    },
    annotations: { readOnlyHint: true },
    execute() {
      const s = read();
      return {
        screen: s.view,
        parameters: s.params,
        usb: s.usb,
        warning: s.warning,
        pending: !!s.pending,
      };
    },
  });
  register({
    name: 'configure_laser_demo_parameters',
    description:
      'Adjust simulated parameters on the main screen. Pending treatment records must be saved or discarded before parameters can be changed.',
    inputSchema: {
      type: 'object',
      properties: {
        power: { type: 'number', minimum: 1, maximum: 100 },
        on: { type: 'number', minimum: 10, maximum: 2000 },
        off: { type: 'number', minimum: 10, maximum: 2000 },
        aim: { type: 'number', minimum: 0, maximum: 100 },
        mode: { type: 'string', enum: ['CW', 'Pulsed'] },
      },
      additionalProperties: false,
    },
    annotations: { readOnlyHint: false },
    execute(input) {
      if (read().view !== 'main')
        throw new Error('Return to the main parameter screen first.');
      if (!input || typeof input !== 'object' || Array.isArray(input))
        throw new Error('Expected a parameter object.');
      for (const [key, value] of Object.entries(input)) {
        if (key === 'mode') {
          if (!['CW', 'Pulsed'].includes(value))
            throw new Error('Unknown mode.');
          continue;
        }
        const limit = LIMITS[key];
        if (
          !limit ||
          typeof value !== 'number' ||
          !Number.isFinite(value) ||
          value < limit[0] ||
          value > limit[1] ||
          value % limit[2] !== 0
        )
          throw new Error(`Invalid demo parameter: ${key}`);
      }
      configure(input);
      return { parameters: read().params, pending: !!read().pending };
    },
  });
  return () => lifecycle.abort();
}
