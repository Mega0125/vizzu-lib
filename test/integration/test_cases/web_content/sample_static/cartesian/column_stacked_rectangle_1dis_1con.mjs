import { data } from '/test/integration/test_data/chart_types_eu.js';

const testSteps = [
  chart => chart.animate({
    data: data,
    config: {
      channels: {
        y: { set: ['Joy factors', 'Value 2 (+)'] },
        color: { set: ['Joy factors'] },
        label: { set: ['Value 2 (+)'] }
      },
      title: 'Stacked Column Chart'
    }
  })
];

export default testSteps;