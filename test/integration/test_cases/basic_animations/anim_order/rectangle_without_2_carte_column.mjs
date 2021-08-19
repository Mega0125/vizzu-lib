import { data } from '/test/integration/test_data/chart_types_eu.js';

const testSteps = [
    chart => chart.animate(
        {
            data: data,
            descriptor:
            {
                channels:
                {
                    color: { attach: ['Threat'] },
                    size: { attach: ['Positive nums'] }
                },
                title: '1D, 1C - Treemap'
            },
            style: {
                plot: {
                    paddingLeft: -50,
                    marker: {
                        borderWidth: 1,
                        borderOpacity: 0.1,
                        borderOpacityMode: 'straight'
                    }
                }
            }
        }
    ),
    chart => 
    {
        console.log(chart.styles);
        console.log(chart.descriptor);
        return chart;
    },
    chart => chart.animate(
        {
            descriptor: {
                channels:
                {
                    x: { attach: ['Threat'] },
                    y: { attach: ['Positive nums'] },
                    size: { detach: ['Positive nums'] }
                },
                title: 'Y C, X D (X first) - Column'
            },
            style: {
                plot: {
                    marker: {
                        label: { fontSize: 6 }
                    }
                }
            }
        }
    ),
        chart => chart.animate(
            {
                descriptor: {
                    channels:
                    {
                        x: { detach: ['Threat'] },
                        y: { detach: ['Positive nums'] },
                        size: { attach: ['Positive nums'] }
                    },
                    title: 'Y C, X D (Y first) - Treemap'
                },
                style: {
                    plot: {
                        marker: {
                            label: { fontSize: 6 }
                        }
                    }
                }
            },
        {
            'x':
             {delay: 1.5}
        }
    ),
    chart => chart.animate(
        {
            descriptor: {
                channels:
                {
                    lightness: { attach: ['Positive nums'] },
                    label: { attach: ['Country_code'] },
                    size: { attach: ['Positive nums', 'Country_code'] }
                },
                title: 'Y C+D, X D - Treemap.'
            },
            style: {
                plot: {
                    marker: {
                        label: { fontSize: 8 }
                    }
                }
            }
        },
        {
            'y':
             {delay: 1.5}
        }
    ),
    chart => chart.animate(
        {
            descriptor: {
                channels:
                {
                    x: { attach: ['Threat'] },
                    y: { attach: ['Positive nums', 'Country_code'] },
                    size: { detach: ['Positive nums'] }
                },
                title: 'Y C+D, X D (X first) - Column'
            }
        },
        {
            'y':
             {delay: 1.5}
        }
    ),
    chart => chart.animate(
        {
            descriptor: {
                channels:
                {
                    x: { detach: ['Threat'] },
                    y: { detach: ['Positive nums', 'Country_code'] },
                    size: { attach: ['Positive nums', 'Country_code'] },
                },
                title: 'Y C+D, X D (Y first) - Treemap'
            }
        },
        {
            'x':
             {delay: 1.5}
        }
    ),
    chart => chart.animate(
        {
            descriptor: {
                channels:
                {
                    x: { attach: ['Threat'] },
                    y: { attach: ['Positive nums', 'Country_code'] },
                    size: { detach: ['Positive nums'] }
                },
                title: 'Y C+D, X D (X first) - Column'
            }
        },
        {
            'y':
             {delay: 1.5}
        }
    ),
    chart => chart.animate(
        {
            descriptor: {
                channels:
                {
                    x: { attach: ['Pos_small'] }
                },
                title: 'Y C+D, X D+C - Mekko'
            }
        },
        {
            'y':
             {delay: 1.5}
        }
    ),
    chart => chart.animate(
        {
            descriptor: {
                channels:
                {
                    x: { detach: ['Threat','Pos_small'] },
                    y: { detach: ['Positive nums', 'Country_code'] },
                    size: { attach: ['Positive nums', 'Country_code'] },
                },
                title: 'Y C+D, X D+C (Y first) - Treemap'
            }
        },
        {
            'x':
             {delay: 1.5}
        }
    ),
    chart => chart.animate(
        {
            descriptor: {
                channels:
                {
                    label: { detach: ['Country_code'] },
                    size: { detach: ['Country_code'] },
                    lightness: { detach: ['Positive nums'] }
                },
                title: 'Y C, X D+C - Treemap'
            }
        },
        {
            'x':
             {delay: 1.5}
        }
    ),
    chart => chart.animate(
        {
            descriptor: {
                channels:
                {
                    x: { attach: ['Threat','Pos_small'] },
                    y: { attach: ['Positive nums'] },
                    size: { detach: ['Positive nums'] },
                },
                title: 'Y C, X D+C (X first) - Mekko'
            }
        },
        {
            'y':
             {delay: 1.5}
        }
    ),
    chart => chart.animate(
        {
            descriptor: {
                channels:
                {
                    x: { detach: ['Pos_small'] }
                },
                title: 'Y C, X D (X first) - Mekko'
            }
        },
        {
            'y':
             {delay: 1.5}
        }
    )
];

export default testSteps;